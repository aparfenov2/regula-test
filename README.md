Regula test solution

build
------------
Windows: cd build; conf.cmd; build.cmd
Linux:   cd build-linux; conf.sh; make; make install

build/debug contains prebuilt Windows binaries

external dependencies
------------
         | Windows             | Linux
opencv   | download & build  | apt-get install
boost    | download & build  | apt-get install
gtest    | download & build  | download & build

folder structure
-----------------
etc              - etc folder from opencv installation
regulaDll.dll    - dll libarry
conApp.exe       - console app
gtestApp.exe     - unit tests app

running on linux
-----------------
LD_LIBRARY_PATH=. ./conApp
