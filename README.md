<h1 align="center">Age of Empires III (2007)</h1>

<p align="center">
  <img src="https://cdn.discordapp.com/attachments/1005443763667206194/1041997462015062056/age3coin.png" alt="AOE3 Legacy Logo">
</p>

<h2 align="center">Individual AI difficulty for UnHardCoded AOE3</h2>

### What is this?

This is a simple UHC Plugin that allows you to select a different difficulty for each AI player.

### Why not just set a handicap?

Because certain AI behaviors depend on the difficulty, not on the handicap. For example, in the *Easy* difficulty, the AI is set to never attack opponents until it gets attacked first.

### Is that it?

For now, yes. But if this plugin appears to have a certain success in the community, it might be expanded to allow other features related to the AI &#8212; force rushing/booming, allow cheats, etc.

### How do I install this?

> ⚠️ The following files have been modified in this plugin:
> * bin\data\uimainnew.xml
> * bin\data\uiskirmishsetup.xml
> * bin\data\uiskirmoptionsdlg.xml
> If you're a non-modder and you want to install this plugin on another mod, please discuss with the mod's author first.
> If you're a modder and these files are already modified in your mod, you will have to make all the necessary adjustments yourself.
> TODO: file diffs

1. Head over the [Releases section](https://github.com/thinotmandresy/age3-individual-ai-difficulties/releases).
2. Download the version you want to install (the latest version is recommended).
3. Put the `age3-player-difficulty.upl` file into the same location where your copy of AOE3 is installed.
   Example: `C:\Program Files (x86)\Steam\steamapps\common\Age of Empires 3\bin\`
4. Still in that same location, find the `Startup` folder and open it.
5. Find the UHC configuration file and open it with Notepad. By default, it is named `uhc.cfg`, but you may have changed it &#8212; please just make sure you're opening the correct file.
6. Make a new line at the end of the file, and paste the following line:

```txt
customSyscalls age3-player-difficulty.upl
customCheats
```

7. Save.
8. Now you can mod the UI files to use the commands provided by the plugin. Go to [this page](https://github.com/thinotmandresy/age3-individual-ai-difficulties/tree/main/data) to see some examples of modded UI.

### This looks interesting. Can we talk?

Sure thing! You can find me as **AlistairJah#3499** on [ImpMod Discord Server](https://discord.gg/WRvuVFg) if you have more questions or simply want to chat :)
