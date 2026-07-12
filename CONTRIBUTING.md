# Contributing to the Persistent Memory Development Kit

Please [contact us](README.md#contact-us) before contributing any changes.

**NOTE**: We do not accept feature requests not related to the [DAOS Project](https://daos.io/).

**NOTE: When implementing code changes and contribute them,
please make sure you agree your contribution can be made available
under the [BSD-style License used for the Persistent Memory Development Kit](LICENSE.txt).**

**NOTE: Submitting your changes also means that you certify the following:**

```
Developer's Certificate of Origin 1.1

By making a contribution to this project, I certify that:

(a) The contribution was created in whole or in part by me and I
    have the right to submit it under the open source license
    indicated in the file; or

(b) The contribution is based upon previous work that, to the best
    of my knowledge, is covered under an appropriate open source
    license and I have the right under that license to submit that
    work with modifications, whether created in whole or in part
    by me, under the same open source license (unless I am
    permitted to submit under a different license), as indicated
    in the file; or

(c) The contribution was provided directly to me by some other
    person who certified (a), (b) or (c) and I have not modified
    it.

(d) I understand and agree that this project and the contribution
    are public and that a record of the contribution (including all
    personal information I submit with it, including my sign-off) is
    maintained indefinitely and may be redistributed consistent with
    this project or the open source license(s) involved.
```

In case of any doubt, the gatekeeper may ask you to certify the above in writing,
i.e. via email or by including a `Signed-off-by:` line at the bottom
of your commit comments.

To improve tracking of who is the author of the contribution, we kindly ask you
to use your real name (not an alias) when committing your changes to the
Persistent Memory Development Kit:
```
Author: Random J Developer <random@developer.example.org>
```

### Code Contributions

The Persistent Memory Development Kit project uses the common
*fork and merge* workflow used by most GitHub-hosted projects.
The [Git Workflow blog article](https://pmem.io/2014/09/09/git-workflow.html)
describes our workflow in more detail.

Before contributing please remember to run:
```
	$ make cstyle
```

This will check all C/C++ files in the tree for style issues. To check C++
files you have to have clang-format version 14.0, otherwise they will be
skipped. If you want to run this target automatically at build time, you can
pass CSTYLEON=1 to make. If you want cstyle to be run, but not fail the build,
pass CSTYLEON=2 to make.
There is also a target for automatic C++ code formatting, to do this run:
```
	$ make format
```

There are cases, when you might have several clang-format-X.Y binaries and either
no clang-format or it pointing to an older version. In such case run:
```
	$ make CLANG_FORMAT=/path/to/clang-format cstyle|format
```

### Bug Reports

Before reporting a new bug please check if it is not already known: [here](https://daosio.atlassian.net/issues?jql=component%20%3D%20PMDK%20ORDER%20BY%20created%20DESC) or [here](https://github.com/pmem/pmdk/issues).

To report a bug please [contact us](README.md#contact-us) and use the [template](.github/ISSUE_TEMPLATE/bug_report.md).

#### PMDK version

Put the release name of the version of PMDK running when the
bug was discovered in a bug comment.  If you saw this bug in multiple PMDK
versions, please put at least the most recent version and list the others
if necessary.
- Stable release names are in the form `#.#.#` (where `#` represents
  an integer); for example `2.1.0`.
- Release names from working versions look like `#.#.#+b#` (adding a build #)
  or `#.#.#-rc#` (adding a release candidate number)
If PMDK was built from source, the version number can be retrieved
from git using this command: `git describe`

For binary PMDK releases, use the entire package name.
For RPMs, use `rpm -q pmdk` to display the name.
For Deb packages, run `dpkg-query -W pmdk` and use the
second (version) string.

#### Priority

Requested priority describes the urgency to resolve a defect and establishes
the time frame for providing a verified resolution. Priorities are defined as:

* **P1**: Showstopper bug, requiring a resolution before the next release of the
library.
* **P2**: High-priority bug, requiring a resolution although it may be decided
that the bug does not prevent the next release of the library.
* **P3**: Medium-priority bug.  The expectation is that the bug will be
evaluated and a plan will be made for when the bug will be resolved.
* **P4**: Low-priority bug, the least urgent.  Fixed when the resources are available.
