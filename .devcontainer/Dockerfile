FROM mcr.microsoft.com/devcontainers/base:windows

SHELL ["powershell", "-NoLogo", "-Command"]

# Install Chocolatey and common build utilities
RUN Set-ExecutionPolicy Bypass -Scope Process -Force; \
    [Net.ServicePointManager]::SecurityProtocol = [Net.SecurityProtocolType]::Tls12; \
    iex ((New-Object System.Net.WebClient).DownloadString('https://community.chocolatey.org/install.ps1')); \
    choco install -y git cmake ninja python --no-progress; \
    refreshenv

# Install Visual Studio Build Tools with the VC toolset (for msbuild / cl.exe)
RUN Invoke-WebRequest -Uri 'https://aka.ms/vs/17/release/vs_BuildTools.exe' -OutFile 'vs_BuildTools.exe' -UseBasicParsing; \
    Start-Process .\vs_BuildTools.exe -ArgumentList '--quiet --wait --norestart --nocache --installPath C:\BuildTools --add Microsoft.VisualStudio.Workload.VCTools --add Microsoft.VisualStudio.Component.VC.Tools.x86.x64 --includeRecommended' -NoNewWindow -Wait; \
    Remove-Item .\vs_BuildTools.exe

ENV PATH="C:\\BuildTools\\MSBuild\\Current\\Bin;C:\\Program Files\\Git\\bin;C:\\ProgramData\\chocolatey\\bin;${PATH}"
