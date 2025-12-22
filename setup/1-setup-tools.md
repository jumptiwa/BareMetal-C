# BareMetal-C Tool Setup for Windows / macOS

## 0. Conventions, guidelines, and WSL preparation
### Conventions:
This is what you should type or copy & paste into computer (example):
```
type, paste, or take action. 
```
and if you see a vertical line **`|`** to the left of a box,
the text in the box with **`|`** on the left is the output from the computer (example):
> ```
> I am the output from the computer
> ```
- **Windows:** contains specific Windows only information.
- **macOS:** contains specific macOS only information.
### Guidelines:
- Whatever folder you choose, make sure there is no `space` in the path name:
- We recommend you to use your `Documents` folder:
  - **Windows recommended location:**
    ```
	C:\Users\NAME\Documents\BareMetal-C
	```
  - **macOS recommended location:**
    ```
	/Users/NAME/Documents/BareMetal-C
	```

### WSL prepartion (Windows only):
  Click `Windows start button` and type:
  ```
  turn windows features on or off
  ```
  Run it. Scroll down and check ✔
  ```
  ☑ Windows Subsystem for Linux
  ```
  and click OK.

  Reboot if necessary.

  **Check your current WSL version:**
  - Type `Win+R` and run `cmd` or `powershell` and type:
    ```
    wsl --version
    ```
  - If it says `WSL version: 2.x`, you're ok.
    
    But if it is `1.x`, you must update `WSL` to `WSL2` by:
    ```
    wsl --update
    ```
    Reboot.

    After reboot, do `wsl --version` again to check that you are on `WSL version: 2.x`.
  
---

## 1. (Windows & macOS) Install Github Desktop

- Download GitHub desktop from [here](https://desktop.github.com/download/).
- Run it. You don't need to sign up, but you need to provide an email address and name. It's best that you **do not share** email addresses with friends. It can cause problems later.
- From **File** menu, click **Clone a repository from the internet** and select **URL**.
- Clone the following URL:
  ```
  https://github.com/kongkrit/BareMetal-C
  ```
- Choose **Local path**.
- For **Windows & macOS:** We *will only support* you if you use `Documents` folder. So, **read carefully:**
  - *Github Desktop* will try to foce you to use `Documents/GitHub` folder. **Override** it!
  - **Windows:** MUST use **Local path** `C:\Users\NAME\Documents\BareMetal-C`
  - **macOS:** MUST use **Local path** `/Users/NAME/Documents/BareMetal-C`
- Click `Clone` and wait for it to finish. Now everything resides in `Documents/BareMetal-C` folder.

---

## 2. (Windows & macOS) Install Docker Desktop 

- Make sure you have *admin rights* on your computer. That is, you can install new programs for all users, etc.
- Make sure you don't have anything important running. `Docker Desktop` may force you to log out to complete the installation.
- Download `Docker Desktop` from [here](https://www.docker.com/products/docker-desktop/).
  Click *Download Docker Destop* and choose the drop down that matches your computer's CPU:
  - **Windows:** Choose `Windows AMD64`
  - **macOS with M-series chip** (starting in late 2020): `Mac - Apple Silicon`
  - **Older macOS with Intel CPU** (before late 2020): `Mac - Intel Chip`

- Install `Docker Desktop` and `Accept` Docker Subscription Service Agreement. It's free for personal use.

  ### For Windows:
  - Make sure the following box is **checked ✔. We will use `WSL2`**:
    > ```
    > ☑ Use WSL 2 instead of Hyper-V`
    > ```
  - and we recommend you **not** to install Windows containers:
    > ```
    > ☐ Allow Windows Containers to be used with this installation
    > ```
  - `Add shortcut to desktop` choice is totally up to you.
  - **Afer installation, it will force you to log out.** Just log back in.
  - You can skip all the questions

  ### For macOS:
  - Drag and drop `Docker` into your `Applications` folder
  - Run `Docker` and select `Use recommended settings`
  - You can skip all the questions
  - Accept all the permissions
  - Wait for the docker icon (a whale with containers on top) on menu bar to stop dancing.

  ### For both Windows / macOS:
  - `Accept` Docker Subscription Service Agreement. It's free for personal use.
  - Select `Personal`, not `Work`, and you can skip giving out your email address.
  - You're free to `Skip` answering all other questions as well.
  - **Make sure you get to the `Docker Desktop` main window.** It should have tabs on the left side, like: `Containers`, `Images`, `Volumes`, etc.
  - **Automatically start `Docker Desktop`** every time you start your computer:
    - On `Docker Desktop` main window, on the upper right bar, click `⚙ (gear icon)` for settings, then click `General` tab on the left. We recommend:

    > ```
    > ☑ Start Docker Desktop when you sign in to your computer
    > ☐ Open Docker Dashboard when Docker Destop starts
    > ```
  - Click `Apply` on the bottom right to save settings.
  - You can close `Docker Desktop` main window now.

---

## 3. Prepare to pull the course software container
Windows and macOS instructions are a bit different here.

### For Windows:
- Open **File Explorer** and go to where your project is from GitHub clone above (`Documents/BareMetal-C`) was recommended.
- Go into `BareMetal-C` folder
- **Shift + Right-click** inside the `BareMetal-C` folder window, and select `Open PowerShell window here` or `Open in Terminal`
- You now have a terminal with prompt:
  > ```
  > PS C:\Users\NAME\Documents\BareMetal-C>
  > ```

### For MacOS
- Use **Finder** and go to where your project is from GitHub clone above. (`Documents/BareMetal-C`) was recommended.
- Type `Command + space` and type `terminal` and you get a terminal window
- type "`cd `" (`cd` and one space after)
- drag `BareMetal-C` folder from **Finder** into terminal. terminal now reads: `cd /Users/NAME/Documents/BareMetal-C` and hit `enter`. Your prompt will be:
  > ```
  > name@computername BareMetal-C %
  > ```

---

## 4. Copy sdcc header and test the tool

### For both Windows and macOS:
- Make sure `Docker Desktop` is running.
- Make sure you are at the right folder:
  - **Windows:** `PS C:\Users\NAME\Documents\BareMetal-C>`
  - **macOS:** `name@computername BareMetal-C %`

- **Generate sdcc header:** copy and paste the command below into the command prompt:
  ```
  docker run --rm -v "${PWD}/.vscode:/target" kongkrit/baremetal-c cp -r /usr/share/sdcc/include /target/sdcc-include
  ```
  (**For macOS:** If `terminal` or `docker` asks you for any permission, give it.)

- It should print out stuff like this:
  > ```
  > Unable to find image 'kongkrit/baremetal-c:latest' locally
  > latest: Pulling from kongkrit/baremetal-c
  > f66b55f4c4ef: Pull complete
  >   ...
  > de0aacc391e0: Download complete
  > Digest: sha256:023b1af0e47c782f6314fda3406651b055884f6a268a632623e63f59d7d07e3c
  > Status: Downloaded newer image for kongkrit/baremetal-c:latest
  > ```
- After a few seconds (depending on your internet speed) the prompt will return. Copy and paste the following into prompt:
  ```
  ls .vscode/sdcc-include/stdi*.h
  ```
  You should see `stdint.h` and `stdio.h` somewhere in the output.

- Copy and paste the command below into command prompt:
  ```
  docker run --name baremetal-c --rm -it -v ${PWD}:/student kongkrit/baremetal-c
  ```
- Your prompt will change to:
  > ```
  > Welcome to student BareMetal-C Environment
  > [baremetal-c]:/student #
  > ```
  If you get the above prompt, your installation is successful.
- From now on, we will call `[baremetal-c]:/student #` the **tool prompt**.

---

## 5. Test the tools (same for Windows and macOS)

Type all the commands from `[baremetal-c]:/student #` prompt (from now on, we will call `[baremetal-c]:/student #` the **tool-prompt** to indicate that you can only run tools from here):

### Check `sdcc` `z80dasm` and `make` -- all from **tool-prompt**:

Check `sdcc`:
```bash
sdcc --version
```
It should say: `SDCC : mcs51/z80/.../f8 TD- 4.5.0 #15242 (Linux)`

Check `sdasz80`:
```bash
sdasz80 2>&1 | head -n 3
```
It should say: `sdas Assembler V02.00 + NoICE + SDCC mods  (Zilog Z80...)`

Check `z80dasm`:
```bash
z80dasm -V
```
It should say: `z80dasm, Z80 assembly language generating disassembler...`

Check compilation:

We run code from `code` folder inside
```bash
cd code
```
and we use `make` to build our C programs.
```bash
make 000-run.bin
```

and it should say (not exactly, but very similar):
> ```
> sdasz80 -l -o default-startup.rel default-startup.s
> sdcc -mz80 --std c99 --Werror  -c 000-test-mem-nmi-for-00.c -o 000-test-mem-nmi-for-00.rel
> [000] NON_HANDLER_OBJ:
> [000] HANDLER_OBJ:     000-test-mem-nmi-for-00.rel
> [000] STARTUP_OBJ:     000-startup.rel
> [000] MEMMAP:          000-memmap.ld
> sdcc -mz80 --no-std-crt0 000-startup.rel 000-test-mem-nmi-for-00.rel  -Wl-u -Wl-f,000-memmap.ld -o 000-run.ihx
> ...Generating Binary and Disassembly 000-run.bin and 000-run.txs...
> sdobjcopy -I ihex -O binary 000-run.ihx 000-run.bin
> z80dasm -a -l -t -g0 000-run.bin 2> /dev/null
> ----------------------------------------------------------------
> ```

and finally
```
make clean
```

and it should say:
>  ```
>  rm -f *.asm *.bin *.ihx *.lk *.lst *.map *.noi *.rel *.rst *.sym *.txs
>  ```

---

## 6. How to logout of the tool prompt.
and get back to `tool-prompt`:

Log out of **tool-prompt**. Easy. type `ctrl + d` or type `exit` and you will see:
> ```
> [baremetal-c]:/student/... #
> exit
> ```
and the prompt changes to `PS C:\...` (Windows), or `name@computername BareMetal-C %` (macOS)

---

## 7. How to get back to the **tool-prompt**:
- Make sure that `Docker Desktop` is running.
- Make sure you're in the correct folder (`BareMetal-C`).
- Repeat steps in section **4. Launching the tool environment** [above](#4-pull-and-launch-the-tool-environment).
