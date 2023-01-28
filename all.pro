CONFIG += c++17 debug
QMAKE_CXXFLAGS += -Wall

include(ui/ui.pri)

DESTDIR = build
OBJECTS_DIR = $$DESTDIR\objects
MOC_DIR = $$DESTDIR\moc
TARGET = svgedit

CONFIG += run_post_build

unix {
   TEST_CMD = "./build/svgedit"
   test.target = test
   test.depends = FORCE
   test.commands = $$TEST_CMD

   regen.target = regen
   regen.depends = distclean
   regen.commands = "qmake6 && make"

   QMAKE_EXTRA_TARGETS += test regen

   run_post_build {
      QMAKE_POST_LINK += $$TEST_CMD
   }
}
