# Improvements to C# analysis

## General improvements

## New queries

| **Query**                   | **Tags**  | **Purpose**                                                        |
|-----------------------------|-----------|--------------------------------------------------------------------|

## Changes to existing queries

| *@name of query (Query ID)*  | *Impact on results*    | *How/why the query has changed*   |
|------------------------------|------------------------|-----------------------------------|
| Off-by-one comparison against container length (cs/index-out-of-bounds) | Fewer false positives | Results have been removed when there are additional guards on the index. |
| Dereferenced variable is always null (cs/dereferenced-value-is-always-null) | Improved results | The query has been rewritten from scratch, and the analysis is now based on static single assignment (SSA) forms. The query is now enabled by default in LGTM. |
| Dereferenced variable may be null (cs/dereferenced-value-may-be-null) | Improved results | The query has been rewritten from scratch, and the analysis is now based on static single assignment (SSA) forms. The query is now enabled by default in LGTM. |
| SQL query built from user-controlled sources (cs/sql-injection), Improper control of generation of code (cs/code-injection), Uncontrolled format string (cs/uncontrolled-format-string), Clear text storage of sensitive information (cs/cleartext-storage-of-sensitive-information), Exposure of private information (cs/exposure-of-sensitive-information) | More results | Data sources have been added from user controls in `System.Windows.Forms`. |
 
## Changes to code extraction

* Fix extraction of `for` statements where the condition declares new variables using `is`.
* Initializers of `stackalloc` arrays are now extracted.

## Changes to QL libraries

## Changes to the autobuilder
