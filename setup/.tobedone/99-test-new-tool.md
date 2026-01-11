## 🪟 Windows Setup (No Docker Desktop)

1.  **Open PowerShell as Administrator.**
2.  **Paste and run this block:**

    ```powershell
    # --- 1. CLEAN SLATE ---
    wsl --unregister Debian
    
    # --- 2. Install ---
    wsl --install Debian --no-launch
    
    # --- 3. THE NUCLEAR FIX: Edit the Windows Registry ---
    # This tells Windows: "Debian is already installed, and the default user ID is 0 (Root)."
    # This prevents the "Enter new UNIX username" prompt from ever appearing.
    $registryPath = "HKCU:\Software\Microsoft\Windows\CurrentVersion\Lxss"
    $distroGuid = (Get-ChildItem $registryPath | Get-ItemProperty | Where-Object { $_.DistributionName -eq "Debian" }).PSChildName
    Set-ItemProperty -Path "$registryPath\$distroGuid" -Name "DefaultUid" -Value 0
    
    # --- 4. Configure wsl.conf (Just to be safe for the future) ---
    wsl -d Debian -u root -e bash -c 'echo -e "[user]\ndefault=root\n\n[boot]\ncommand=service docker start" > /etc/wsl.conf'
    
    # --- 5. Install Docker ---
    $dockerInstallCmd = @'
    apt-get update
    apt-get install -y ca-certificates curl gnupg
    install -m 0755 -d /etc/apt/keyrings
    curl -fsSL https://download.docker.com/linux/debian/gpg | gpg --dearmor -o /etc/apt/keyrings/docker.gpg
    chmod a+r /etc/apt/keyrings/docker.gpg
    echo "deb [arch=$(dpkg --print-architecture) signed-by=/etc/apt/keyrings/docker.gpg] https://download.docker.com/linux/debian $(. /etc/os-release && echo "$VERSION_CODENAME") stable" > /etc/apt/sources.list.d/docker.list
    apt-get update
    apt-get install -y docker-ce docker-ce-cli containerd.io docker-buildx-plugin docker-compose-plugin
    '@
    wsl -d Debian -u root -e bash -c $dockerInstallCmd
    
    # --- 6. Restart ---
    wsl --shutdown
    
    Write-Host "Setup Complete. Type 'wsl'—it should jump straight to root." -ForegroundColor Green
    ```

3.  **Verification:**
    Open a new PowerShell and type `wsl docker --version`.
