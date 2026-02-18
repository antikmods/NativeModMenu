# ==========================================================
#                  NATIVE MOD MENU (NMM)
# ==========================================================
#  A custom high-performance reimplementation of the LGL 
#  Android Mod Menu with In-Memory Dex Loading.
# ==========================================================

[ DESCRIPTION ]
NativeModMenu is a stealth-oriented implementation that loads 
the Java UI layer entirely from memory using InMemoryDexClassLoader. 
By embedding the FloatingModMenu.dex as a HEX string, it eliminates 
the need for shipping or extracting external .dex files on disk.

[ CORE ARCHITECTURE ]
- ZERO DISK FOOTPRINT: No external dex file or asset extraction.
- MEMORY LOADING: Utilizes dalvik.system.InMemoryDexClassLoader.
- JNI BOOTSTRAP: Menu initialization triggered via native code.
- CLEAN INJECTION: Stealthier footprint for modern environments.
- FULL COMPATIBILITY: Supports existing LGL Java-based menu code.

[ TECHNICAL WORKFLOW ]
1. DEX EMBEDDING: FloatingModMenu.dex is stored as a HEX string.
2. BUFFER CONVERSION: HEX string is parsed into a ByteBuffer at runtime.
3. DYNAMIC LOADING: InMemoryDexClassLoader loads the buffer directly.
4. NATIVE BINDING: JNI registers functions to the Java menu class.
5. EXECUTION: Calls 'FloatingModMenu.antik(Context)' to launch.

[ JNI NATIVE INTERFACE ]
The following methods are registered dynamically:

- Icon()              : Returns menu icon data.
- IconWebViewData()   : Returns WebView-based icon data.
- getFeatureList()    : Defines the menu features.
- settingsList()      : Defines the menu settings.
- Changes(...)        : Handles feature toggles and logic.
- setTitleText(...)   : Customizes the menu title.
- setHeadingText(...) : Customizes the menu heading.

[ SYSTEM REQUIREMENTS ]
- OS      : Android 8.0+ (API Level 26+)
- ARCH    : ARMv7, ARM64-v8a
- RUNTIME : JNI-based injection environment
- ASSET   : Prebuilt compatible FloatingModMenu.dex

[ ENTRY POINT ]
- Function: void binJava()
- Executed post JNI_OnLoad.
- Context acquisition via ActivityThread.

[ LEGAL & ETHICAL NOTICE ]
This project is intended for educational and research purposes 
only. Modifying runtime behavior of applications may violate 
Terms of Service. Use responsibly.

[ CREDITS ]
- Original Concept : LGL Android Mod Menu
- Project Lead     : AntikMods
- Dex Loader Logic : NepMods
# ==========================================================
