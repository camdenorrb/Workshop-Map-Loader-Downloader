This was my first ever c++ project. I learned c++ while I was developing it so the code is pretty bad not gonna lie.

# Workshop Map Loader & Downloader

This plugin allows you :

- To load Workshop Maps from a folder. 

 ![Map Loader Tab](https://i.postimg.cc/bYMgjV2C/1ere-Partie.png)


- To search a map on the steam workshop directly on the plugin interface.

 ![Search Workshop Tab](https://i.postimg.cc/VNYBF336/2eme-Partie.png)


- To download a map from an url, or, from the searching results into your maps folder

### Additional Informations

- This plugin can be used by Epic Games users.

- Languages : English or French.

- Add a bind to open the plugin window :
    - **F2->bindings**, add a bind with this command line : `"togglemenu WorkshopMapLoaderMenu"`
    - **F2->plugins->WorkshopMapPlugin**, here you just need to put a Key in the text field, and press "Set Bind".


## Tutorial

You have to :
- Create a folder wherever you want on your computer that will contain the maps
- Open the plugin
- Copy/paste the folder's path into the text field (in the "Map Loader" tab)
- Go in "Search Workshop" tab and search a workshop
    - Put some keywords (ex : Dribbling Challenge, Rings etc...) and press "Search". The results will be displayed below.
- Download a map
    - From The Searching Results :
        - Do a research
        - Click on "Download Map"
    - With Url :
        - Put a Steam workshop url in the text field
        - Click on "Download".
    - Manually :
        - Download a map with [steamworkshopdownloader.io](https://steamworkshopdownloader.io/), create a new folder in your maps folder, then extract the files of the map into this new folder
- Click on "Refresh Maps"
- Choose the map you want to play


I've made a tutorial if you are struggling to make it work : [https://www.youtube.com/watch?v=mI2PqkissiQ](https://www.youtube.com/watch?v=mI2PqkissiQ)

## Building with CMake

1. Install the BakkesMod SDK and note the directory that contains the `bakkesmodsdk/include` and `bakkesmodsdk/lib` folders. Export it via `setx BAKKESMOD_SDK_PATH "C:\path\to\bakkesmodsdk"` or pass it to CMake with `-DBAKKESMOD_SDK_PATH=...`.
2. From a "x64 Native Tools" developer prompt generate the build files (Visual Studio 2022 in this example):
   ```powershell
   cmake -S . -B build -G "Visual Studio 17 2022" -A x64
   ```
3. Build the Release configuration (BakkesMod loads Release DLLs):
   ```powershell
   cmake --build build --config Release
   ```
4. The resulting `WorkshopMapLoader.dll` is written to `build/plugins`. Copy it to `BakkesMod/bakkesmod/plugins/` if you want the game to load it automatically.

### CI builds

This repository includes a GitHub Actions workflow (`.github/workflows/build.yml`) that compiles the plugin on every push/PR. Because the BakkesMod SDK is not publicly downloadable, generate a zip of your local SDK folder, base64-encode it, and store it in a repository secret named `BAKKESMOD_SDK_ZIP_BASE64`. The workflow restores the SDK from that secret, runs the same CMake commands as above, and publishes the built DLL as an artifact.

## Bugs/Issues Known

- If you use Windows 7 you wont be able to load the plugin, add me on discord (just below) I can give you an old version working for Windows 7

- Mutators are not working for clients in a multiplayer server

- If the path you put contains "//" just after the disk name (ex : C://RL maps/), you wont be able to load a map
    - Only put one "/"

- If your game crashes when you click on download
    - This is probably because the place where you have created the maps folder need administrator permission

- If there is accents, arabic or special characters in the path, it tells you "The directory you entered doesn't exist"
    - You have to find a path that doesn't contain these characters .

- If your game crashes when clicking on "Refresh Maps"
    - Maybe because your maps folder contains other things, you need to dedicate the maps folder only for the workshops maps and nothing else
