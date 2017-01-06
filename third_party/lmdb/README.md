LMDB
====

Modified version of LMBD 0.9.19. LMDB is an extraordinarily fast, memory-efficient database. With memory-mapped files, it has the read performance of a pure in-memory database while retaining the persistence of standard disk-based databases.

In other words, it runs like a bat out of hell, performing several times faster than other DB engines. No buffers needed, no memory copies generated.

Modifications are intended to integrate LMDB in ComicKron build only with needed files.

Changelog:
* Remove unneeded upstream files (tests, Makefile, documentation, ...)
* Integrate LMDB in ComicKron build (qmake)

LMDB is licensed under the terms of [OpenLDAP Public License](http://www.openldap.org/software/release/license.html).
