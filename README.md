# Stamp

# Init your repository

```sh
cd ~/repositories/fancy_project/
stamp init .
```

This will create hiden `.stamp` folder in your project.
Now you can add templates to `.stamp/templates/`

# Variables

## Global
| name | description|
| --- | --- |
| %{currentDirectory} | folder of stamp command invocation |
| %{date} | date that looks like Tue Feb 2 2021 |
| %{time} | time that looks like 02:47:18 |
| %{project}| folder where init was invoked i.e. `.stamp` folder is located |
| %{templates}| folder with templates inside `.stamp` folder |

## For `stamp create` operation
| name | description|
| --- | --- |
| %{templateName} | name of template that is used (goes after "create") |
| %{targetPath}| where to copy template content |
| %{targetName}| name of a file for unpacking |