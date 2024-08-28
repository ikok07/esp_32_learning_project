# See the build system documentation in IDF programming guide
# for more information about component CMakeLists.txt files.

file(GLOB_RECURSE SRC_FILES *.*)

idf_component_register(SRCS main.c ${SRC_FILES}
						INCLUDE_DIRS "."
						EMBED_FILES webpage/app.css webpage/app.js webpage/index.html webpage/jquery-3.3.1.min.js webpage/favicon.ico)