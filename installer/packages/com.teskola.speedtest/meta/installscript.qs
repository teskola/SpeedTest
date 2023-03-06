function Component()
{
    installer.installationFinished.connect(this, Component.prototype.installationFinishedPageIsShown);
    installer.finishButtonClicked.connect(this, Component.prototype.installationFinished);
}

Component.prototype.createOperations = function()
{
    component.createOperations();
	
	// Add start menu
	
	if (systemInfo.productType === "windows") {
        component.addOperation("CreateShortcut", "@TargetDir@/SpeedTest.exe", "@StartMenuDir@/SpeedTest.lnk",
            "workingDirectory=@TargetDir@", "iconPath=%SystemRoot%/system32/SHELL32.dll",
            "iconId=2", "description=Launch SpeedTest");
			
		component.addOperation("CreateShortcut", "@TargetDir@/SpeedTest.exe", "@DesktopDir@/SpeedTest.lnk",
				"workingDirectory=@TargetDir@", "iconPath=%SystemRoot%/system32/SHELL32.dll",
				"iconId=2", "description=Launch SpeedTest");
    }
	
}

Component.prototype.installationFinishedPageIsShown = function()
{
    try {
        if (installer.isInstaller() && installer.status == QInstaller.Success) {
            installer.addWizardPageItem( component, "InstallationFinishedForm", QInstaller.InstallationFinished );
        }
    } catch(e) {
        console.log(e);
    }
}

Component.prototype.installationFinished = function()
{
    try {
        if (installer.isInstaller() && installer.status == QInstaller.Success) {
            var checkboxForm = component.userInterface( "InstallationFinishedForm" );
            if (checkboxForm && checkboxForm.readMeCheckBox.checked) {
                QDesktopServices.openUrl("file:///" + installer.value("TargetDir") + "/README.txt");
            }
			if (checkboxForm && checkboxForm.launchCheckBox.checked) {
                // installer.performOperation("Execute", [installer.value("TargetDir") + "/SpeedTest.exe"]);
				installer.executeDetached(installer.value("TargetDir") + "/SpeedTest.exe");
			}			
        }
    } catch(e) {
        console.log(e);
    }
}

