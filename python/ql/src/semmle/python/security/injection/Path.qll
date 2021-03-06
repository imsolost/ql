import python

import semmle.python.security.TaintTracking
import semmle.python.security.strings.Untrusted

/** Prevents taint flowing through ntpath.normpath()
 * NormalizedPath below handles that case.
 */
private class PathSanitizer extends Sanitizer {

    PathSanitizer() {
        this = "path.sanitizer"
    }

    override predicate sanitizingNode(TaintKind taint, ControlFlowNode node) {
        taint instanceof ExternalStringKind and
        abspath_call(node, _)
    }

}

private FunctionObject abspath() {
    exists(ModuleObject os, ModuleObject os_path |
        os.getName() = "os" and
        os.getAttribute("path") = os_path |
        os_path.getAttribute("abspath") = result
        or
        os_path.getAttribute("normpath") = result
    )
}

/** A path that has been normalized, but not verified to be safe */
class NormalizedPath extends TaintKind {

    NormalizedPath() {
        this = "normalized.path.injection"
    }

    override string repr() {
        result = "normalized path"
    }

}

private predicate abspath_call(CallNode call, ControlFlowNode arg) {
    call.getFunction().refersTo(abspath()) and
    arg = call.getArg(0)
}


class AbsPath extends DataFlowExtension::DataFlowNode {

    AbsPath() {
        abspath_call(_, this)
    }

    override
    ControlFlowNode getASuccessorNode(TaintKind fromkind, TaintKind tokind) {
        abspath_call(result, this) and tokind instanceof NormalizedPath and fromkind instanceof ExternalStringKind
    }

}

class NormalizedPathSanitizer extends Sanitizer {

    NormalizedPathSanitizer() {
        this = "normalized.path.sanitizer"
    }

    override predicate sanitizingEdge(TaintKind taint, PyEdgeRefinement test) {
        taint instanceof NormalizedPath and
        test.getTest().(CallNode).getFunction().(AttrNode).getName() = "startswith" and
        test.getSense() = true
    }

}

/** A taint sink that is vulnerable to malicious paths.
 * The `vuln` in `open(vuln)` and similar.
 */
class OpenNode extends TaintSink {

    override string toString() { result = "argument to open()" }

    OpenNode() {
        exists(CallNode call |
            call.getFunction().refersTo(builtin_object("open")) and
            call.getAnArg() = this
        )
    }

    override predicate sinks(TaintKind kind) {
        kind instanceof ExternalStringKind
        or
        kind instanceof NormalizedPath
    }

}





