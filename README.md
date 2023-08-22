  
#  f446-mbed-template

先輩が作ってくれたテンプレート
https://github.com/KeioRoboticsAssociation/F446_Mbed_Template
でピンが通らない問題があり，platformio.iniを編集しても直せそうになかったので
c_cpp_properties.jsonを無理やり書き換えるプログラムを書いて，tasks.jsonに登録したやつです．

# 使い方

.vscode/tasks.jsonの"command"のところをpythonのパスに書き換えて使ってください

```json
{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "edit c_cpp_properties.json",
            "type": "shell",
            "command": "python3", //ここを書き換える必要があるかもしれない
            "args": [
                "${workspaceFolder}/edit_c_cpp_properties.py"
            ],
            "group": "build",
            "runOptions": {
                "runOn": "folderOpen"
            }
        }
    ]
}
```

