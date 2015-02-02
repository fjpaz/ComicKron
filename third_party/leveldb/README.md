LevelDB
=======

Modified version of LevelDB commit 77948e7eec0613fb5cbecb7e320b9498607030b5. LevelDB is a fast key-value storage library written at Google that provides an ordered mapping from string keys to string values. Upstream version [here](https://github.com/google/leveldb).

Modifications are intended to use Qt port when platform is not POSIX.

Changelog:
* Add Qt port from QtWebkit
* Remove unneeded upstream files (tests, build, doc, ...)
* Integrate LevelDB in ComicKron build (qmake)

LevelDB is licensed under the terms of [New BSD License](http://www.opensource.org/licenses/bsd-license.php).

Qt port is licensed under the terms of [LGPL](http://www.gnu.org/copyleft/lesser.html).
