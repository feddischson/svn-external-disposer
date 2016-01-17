<!--- eat my shorts doxygen!! -->
SVN-External-Disposer
=======================

A QT based tool to manage svn:externals.

The svn:externals are a property type used by the subversion version control system
to include different subdirectories from different location into a source code tree.

If a software is build by different libraries, modules or software parts within a 
source-code tree, the configuration of this software can be done with svn:externals.
In this situations, specially of the configuration gets more and more complex,
this tool can help to get an overview which folder is pulled in by a svn:external entry, 
from where it is coming from and which revision is used.

The software can be seen as a file-browser, which is extended by some information about the
svn:externals. It consists a revision-log browser which then helps to select the correct revision.

Further information
   - SVN Documentation about svn:externals: http://svnbook.red-bean.com/en/1.7/svn.advanced.externals.html

and some discussions about svn:externals and why it is maybe not good to use this feature:
   - http://stackoverflow.com/a/345404
   - http://stackoverflow.com/a/304036
   - http://www.christoph-jahn.com/?p=675




Get the source-code
=======================

```
git clone https://github.com/feddischson/svn-externals-disposer.git
```



Dependencies
==============

Build
--------------
This tool depends on QT-5 and a compiler which supports C++11.

Runtime
--------------
The SVN command line tool available in your system environment.
Try to run (on windows via cmd.exe)
```
svn --version
```
to figure out if you have the SVN command line tool with the correct version.
This tool is tested with SVN version 1.8.x.


Build and install this tool
=======================

``` 
qmake svn_externals_disposer.pro
make
make install
```

Create the Documentation
=======================

```
doxygen doxy.cfg
```
The result is placed in `doxydoc`.


Run some tests
=======================

```
qmake test.pro
./test_svn_externals_disposer
```


License
=======================

```
Copyright (C) 2016  Christian Haettich [feddischson]

This program is free software; you can redistribute it 
and/or modify it under the terms of the GNU General Public 
License as published by the Free Software Foundation; 
either version 3 of the License, or (at your option) 
any later version.

This program is distributed in the hope that it will 
be useful, but WITHOUT ANY WARRANTY; without even the 
implied warranty of MERCHANTABILITY or FITNESS FOR A 
PARTICULAR PURPOSE. See the GNU General Public License 
for more details.

You should have received a copy of the GNU General 
Public License along with this program; if not, see 
<http://www.gnu.org/licenses/>. 
```
