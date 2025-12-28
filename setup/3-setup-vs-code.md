# VS Code & Build Environment Setup Guide

This guide will help you set up Visual Studio Code (VS Code) and configure it to work with your Docker-based build environment.

## 0. Prerequisites: Tools and SimulIDE installation

Before setting up VS Code, ensure the tools (which includes *GitHub Desktop* and *Docker Desktop*) and *SimulIDE* are installed and running, as VS Code depends on it.

1. Follow instructions to [setup tools](./1-setup-tools.md).
2. Follow instructions to [setup SimulIDE](./2-setup-simulide.md).

---

## 1. Install Visual Studio Code

### For Windows
1.  Download the **Windows installer** from the official website: [code.visualstudio.com](https://code.visualstudio.com/).
2.  Run the installer (`VSCodeUserSetup-{version}.exe`).
3.  Follow the prompts. **Important:** On the "Select Additional Tasks" screen, *check all 4 boxes*. The last box says: **"Add to PATH (requires shell restart)"**.

    ![VS Code Setup Additional Tasks](./pix/3-code-00-win.png)
5.  Click **Install**.

### For macOS
1.  Download the **macOS Universal build** from the official website: [code.visualstudio.com](https://code.visualstudio.com/).
2.  Open the downloaded zip file.
3.  Drag the `Visual Studio Code.app` into your **Applications** folder.
4.  Launch VS Code.
5.  (Optional but Recommended) Open the Command Palette (`Cmd+Shift+P`), type `Shell Command: Install 'code' command in PATH`, and press Enter.

---

## 2. Open the Workspace

1.  **Quit *VS Code* if it is open.**
2.  Go it `Documents/BareMetal-C` folder using *Windows File Explorer* or *macOS Finder*.
3.  Double click on `student.code-workspace` on that folder. This workspace file *may* show up as `student` if you hide file extension).
   
    (full path is `~/Documents/BareMetal-C/student.code-workspace`)

    **macOS:** If there's any prompt asking you for any permission, give permission.

    **Visual Studio Code** (`VS Code`) will start and ask: `Do you trust the authors of the files in this workspace?`. Click `Yes`.

    ![trust workspace](./pix/3-trust-workspace.png)

4.  Close `VS Code`.

5.  Reopen `VS Code`. If things work correctly, it should come right back to `student.code-workspace`. After running `VS Code` this time, you will see:

    ![workspace name](./pix/3-space-name.png)

    If it doesn't look like the screenshot above, click `Explorer` Icon (1).
    
    Then, check the name at (2). You **must see** the checkmark (✅) and the robot (🤖). The full thing in (2) must be:

    ```
    ✅ BareMetal-C 🤖
    ```

    If it does not look like the above, click `File` and select `Open Workspace from File...` and choose `student.code-workspace`.

**This is the way we start `VS Code` for this class.**

---

## 3. Install the Extensions

1.  While you're installing stuff, the pop-up may appear on the bottom right, asking you to install C/C++ extension. Click `Install`.

    ![c-extension](./pix/3-c-extension.png)

2.  **Add `baremetal-c-builder` extension to VS Code:**

    Click on the `Extensions` icon:

    ![extension icon](./pix/3-code-07.1.png)

3.  Use **Windows File Explorer** or **macOS Finder**, go to `Documents/BareMetal-C/_vscode_extensions` folder.

    Drag file `baremetal-c-builder-0.X.X.vsix` (`X.X` may change) to the *extension area*:

    ![extension area](./pix/3-code-07.2.png)

4.  Close VS Code. Reopen it. Click the `Extensions` icon again. Now `BareMetal-C-Builder` Extension should show up:

    ![extension shown](./pix/3-code-07.3.png)
    
---

## 4. Running the Build Environment

1. Click `Explorer` icon to go back to folder explorer. Then right click on `code` folder:

   ![right click code](./pix/3-code-07.4.png)

2. A context menu opens up, choose `Build BareMetal-C All (Recursive)`

   ![build all](./pix/3-code-07.5.png)

   A lot of text will be printed in the `terminal`, but eventually, you should have all projects built. Look for `(TIME) ------ built PROJECT_NAME.bin -------` like this:

   ![build successful](./pix/3-code-07.6.png)

   **If you got this far, your installation is successful.**

3. Let's try clean up. Right click on folder `code` again, but this time, choose `Clean BareMetal-C All (Recursive)` and you should see `terminal` with the text `(TIME) -------- clean successful --------`

   ![clean successful](./pix/3-code-07.7.png)

---

We will use the **right click on a folder** to `build` and `clean` our programming projects. More instructions later!

---

## 5. Next step:

Go to [test the environment](./4-setup-test.md).
