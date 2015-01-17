Windows Setup
=============
These folders in this directory are required for use in a Visual Studios Project.
See the below steps on how to build curl, and create a Visual Studios Project that uses the iSENSE C++ class.

Steps required:
===============
1. Build libcurl from source for Windows
2. Add libcurl to a Visual Studios Project
3. Add the API files to the same project
4. Add your main as well.

I've already built libcurl from source, so all users should need to do is add their main to
a Visual Studio Project along with the "include" and "lib" folders in this directory. This will
require users to download the free Visual Studios 2013 Express. I have not tested the "Community" edition,
but it should work the same, as well as the Professional version (tested & working).

Building Libcurl from source
=============================
1. Download latest zip off of http://curl.haxx.se/download.html (currently it is "curl-7.39.0.zip").
2. Unzip it. (use 7-Zip or another free zip utility)
3. Open up Visual Studios 2013, go to Tools -> Visual Studios Command Prompt 
(Hard to find in the 2013 Express version, easier using the Professional version)
4. From there, cd to where you unzipped the source file. Ex: Downloads\curl-7.39.0
5. Now cd to winbuild. Ex: Downloads\curl-7.39.0\winbuild 
6. Run the following command:

``` 
nmake /f Makefile.vc mode=static VC=12 DEBUG=yes
```

This will create a build in the "builds" folder that will work in Visual Studios 2013.
There will probably be 3 different folders in the builds folder. You will want to navigate
into the one containing 3 folders: bin, include, and lib.

Adding libcurl to a Visual Studios Project
===========================================
You'll need to add the include and lib folders to a Visual Studios Project.
Note: To add some of these items, you need to click on the box to the right of the option, 
which will display an arrow to on the right side, and then click on "edit". 
Make sure to click Apply and then OK.

I recommend creating a "source" directory in your project folder. This will keep everything organized.
You can then put the "include" and "lib" folders into the "source" directory and you can also add the
iSENSE class, as well as your main.

1. Right click on the project name in the solution explorer, then click on "Properties"
2. Click on Configuration Properties, then C/C++ and go to General, then at the very top click on
"Additional Include Directories" and add a link to the curl folder inside the builds/windows folder.
3. Now go to C/C++ -> Preprecessor, click on the top "Preprocessor definitions" and add the two following lines:

CURL_STATICLIB
_CRT_SECURE_NO_WARNINGS

The CRT SECURE NO WARNINGS is to prevent Visual Studios from complaining.

4. Next go to Linker -> General and then click on "Additional Library Directories" and add
a link to the libcurl folder in the builds/windows folder.
5. Finally, go to Linker -> Input and click on "Additional Dependencies" and add the following:
libcurl.lib

Add the API files to the project
===================================
You will also want to add the API files to the same "source" directory. Header files can go in 
the include folder, and you will want to put the api.cpp file as well as your main.cpp directory
into the source folder.

You will also want to add these files to the Visual Studios Project so that Visual Studios can see them
and so that you can edit. You will likely not need to edit the API files but you may want to look inside the
header files to see what methods the API provides. Visual Studios also needs to know where these files are.

You should open the Solution Explorer, and right click on the "Header Files", and then Add -> Existing file.
Add the following this way:
API.h
memfile.h
picojson.h

Next right click on the "Source Files" option and add the existing api.cpp file as well as your own main.cpp. You can
also add any of the test cpp files found on the GitHub repo, such as POST_isense.cpp.

You should now be able to compile a basic curl program / start testing the iSENSE class.