<p><strong><u>Description:</u></strong></p>
<p>CHADA (Chasing your Dreams and Adventure) is an online shopping command line simulator that allows the purchase of virtual materials. It does not have a main UI yet, so it can serve as a template for integrating an online shop system for a software project. The database is still in a file state, so it does not use any relational database systems. It features the following functionalities:</p>
<ul>
<li>Choose between becoming a buyer or a seller (you can do both)</li>
<li>Have a unique customized selling experience. Virtual materials can have a picture of their own!</li>
<li>Items sold can be categorized</li>
<li>Materials in the file database contains a lot a of free samples</li>
</ul>
<p>&nbsp;</p>
<p><strong><u>GitHub Additional:</u></strong></p>
<p>Building from source:</p>
<p>The Qt Creator IDE 4.3.1 was used in creating this project using Qt 5.9.1. Although it is plainly C++ and no Qt libraries were used, it is still recommended to use the official IDE. To build from source, just clone all of the folders into one directory. The &ldquo;mastercard&rdquo; folder is a DLL external library that is used in conjunction with the TyBank online banking simulator, so just make sure to add it into the build release directory. Run the .pro in the CHADAOnlineShop folder. Build the program so that the build directory will show so that you can add the mastercard library. You can do this by building the mastercard lib, copying the .dll lib onto the CHADAOnlineShop build release, and then copying the .a and .h of the lib onto the main program code. Then, edit the DataHandler::CHADA_DATABASE static const string in the datahandler.cpp of the main program to point to the &ldquo;CHADA Database&rdquo; folder. After that, you should be able to run the console app now.</p>
<p>&nbsp;</p>
<p><strong><u>Screenshots:</u></strong></p>
<p style="text-align: center;"><strong><u><img src="https://raw.githubusercontent.com/markytools/chada-cmd-shop-simulator/master/CHADAOnlineShop/other/screenshot1.png" alt="" width="948" height="464" /></u></strong></p>
<p style="text-align: center;"><strong><u><img src="https://raw.githubusercontent.com/markytools/chada-cmd-shop-simulator/master/CHADAOnlineShop/other/screenshot2.png" alt="" width="960" height="480" /></u></strong></p>
<p><strong><u><img style="display: block; margin-left: auto; margin-right: auto;" src="https://raw.githubusercontent.com/markytools/chada-cmd-shop-simulator/master/CHADAOnlineShop/other/screenshot3.png" alt="" width="907" height="496" /></u></strong></p>
<p style="text-align: center;"><strong><u><img src="https://raw.githubusercontent.com/markytools/chada-cmd-shop-simulator/master/CHADAOnlineShop/other/screenshot4.png" alt="" width="960" height="480" /></u></strong></p>
