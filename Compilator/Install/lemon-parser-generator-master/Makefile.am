SUBDIRS = . src examples

clean-local:
	-rm -rf *~

distclean-local:
	-rm -rf autom4te.cache

log:	.svn
	svn update
	if [ -d /usr/share/locale/en_US.UTF-8 ]; then LC_ALL=en_US.UTF-8; \
	else LC_ALL=en_US.utf8; fi && svn log > ChangeLog
