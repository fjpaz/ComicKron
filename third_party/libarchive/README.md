libarchive
==========

Modified version of libarchive 3.1.2. libarchive is a multi-format archive and compression library. Upstream version [here](https://github.com/libarchive/libarchive).

Modifications are intended to support WinRT and reduce size removing needless features.

Changelog:
* Remove disk I/O support
* Remove support for several formats. Supported formats are: zip, rar, tar, gzip and 7-zip
* Remove tools
* Remove upstream build files
* Integrate libarchive in ComicKron build (qmake)

libarchive is licensed under the terms of [New BSD License](http://www.opensource.org/licenses/bsd-license.php).
