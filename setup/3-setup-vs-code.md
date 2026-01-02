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

    ![VS Code Setup Additional Tasks](./pix/3-win-setup.png)
5.  Click **Install**.

### For macOS
1.  Download the **macOS Universal build** from the official website: [code.visualstudio.com](https://code.visualstudio.com/).
2.  Open the downloaded zip file.
3.  Drag the `Visual Studio Code.app` into your **Applications** folder.
4.  Launch VS Code.
5.  (Optional but Recommended) Open the Command Palette (`Cmd+Shift+P`), type `Shell Command: Install 'code' command in PATH`, and press Enter.

---

## 2. Set the profile and open the Workspace

1.  **Quit *VS Code* if it is open.**

2.  Click this link to open -> [BareMetal-C Student Profile](https://vscode.dev/profile/github/94a028b99feaaaf2c054cec55e6574de)

    Your web browser will open a new page that looks like this:

    ![web profile](./pix/3-web-profile.png)

    Click on `Create in Visual Studio Code` and give permission to your web browser to open `Visual Studio Code`.

    ![allow vscode](./pix/3-allow-vscode.png)

3.  `VS Code` will open a page like below:

    ![create profile](./pix/3-create-profile.png)
	
	Click `Create`.
	
	And the next window will pop up. Click `Trust Publisher and Install`.
	
	![trust publisher](./pix/3-trust-publisher.png)
	
	This will take a while, and finally, VS Code window will show up.

4.  Click the `settings icon` (1). Choose `Profile` (2) and select `BareMetal-C Student` (3).

    ![choose profile](./pix/3-choose-profile.png)

5.  Click `File` and `Open Workspace from File...` 

    ![open workspace](./pix/3-open-workspace.png)

    and choose this file:

	> **Windows:** `C:\Users\NAME\Documents\BareMetal-C\student.code-workspace`

	> **macOS:** `~/Documents/BareMetal-C/student.code-workspace`

6.  When asked `Do you trust the authors of the files in this workspace?`. Click `Yes, I trust the authors`.

    ![trust workspace](./pix/3-trust-workspace.png)

7.  If things work correctly, you will see:

    ![check](./pix/3-space-name.png)

    If it doesn't look like the screenshot above, click `Explorer` Icon (1).
    
    Then, check the name at (2). You **must see** the *checkmark* (✅) and the *robot* (🤖). The full thing in (2) must be:

    `✅ BareMetal-C 🤖`

    If it does not look like the above, close `VS Code` and re-open it and see the steps that you may be missing.

8.  Check extension:

    Clieck `Extensions` button (1), and you should see the extension installed. (2)

    ![check extension](./pix/3-check-extension.png)

**Double clicking `student.code-workspace` is the way we start `VS Code` for this class.**

---

## 4. Running the Build Environment

1. Click `Explorer` icon to go back to folder explorer. Then right click on `code` folder:

   ![right click code](./pix/3-right-click-code.png)

2. A context menu opens up, choose `BareMetal-C` and `Build BareMetal-C Projects (All)`

   ![build all](./pix/3-build-all.png)

   A lot of text will be printed in the `terminal`, but eventually, you should have all projects built. Look for `(TIME) ------ built PROJECT_NAME.bin -------` like this:

   ![built all](./pix/3-built-all.png)

   **If you got this far, your installation is successful.**

3. Let's try clean up. Right click on folder `code` again, but this time, choose `BareMetal-C` and `Clean BareMetal-C Projects (All)` and you should see `terminal` with the text `(TIME) -------- clean successful --------`

   ![cleaned](./pix/3-cleaned.png)

---

We will use the **right click on a folder** to `build` and `clean` our programming projects. More instructions later!

---

## 5. Next step:

Go to [test the environment](./4-setup-test.md).
