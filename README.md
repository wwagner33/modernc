# O que é o wellModernC

Repositório com estudos na linguagem C em ambiente Windows e macOS a fim de entender o funcionamento desta linguagem em seus dialetos e formas mais modernas. Como estou estudando mais sobre o assunto, resolvi compartilhar meus estudos e descobertas. Irei depositar aqui códigos, dicas de material didático e tutoriais de aprendizado da linguagem. O estudo está voltado ao desenvolvimento de algoritmos bioinspirados em linguagem C para uso em UAV, baseado nos trablhos de Patrícia de Sousa Paula.

## Autor
Wellington Wagner F. Sarmento

## Compiladores, ferramentas, instalações e configurações
- **Editor**: Visual Studio Code
- **Extensões para o Editor**: [Microsoft C/C++ Extetion Pack](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools-extension-pack), Bracket Pair Colorizer, [C/C++ Snppets (Hash)](https://marketplace.visualstudio.com/items?itemName=CoenraadS.bracket-pair-colorizer),[Code Runner (.run)](https://marketplace.visualstudio.com/items?itemName=formulahendry.code-runner)
- **Compilador**: [clang](https://clang.llvm.org/get_started.html) ou [gcc for Windows](https://gcc.gnu.org/install/binaries.html)
- **Depurador**: lldb ou gdb
- **Instalações**
- **Configurações**:
> Para macOS
- Arquivo tasks.json
- Retirado de [https://code.visualstudio.com/docs/cpp/config-clang-mac](https://code.visualstudio.com/docs/cpp/config-clang-mac)
```json
{
"version": "2.0.0",
"tasks": [
	{
		"type": "cppbuild",
		"label": "C/C++: clang arquivo de build ativo",
		"command": "/usr/bin/clang",
		"args": [
			"-g",
			"${file}",
			"-o",
			"${fileDirname}/${fileBasenameNoExtension}"
		],
		"options": {
			"cwd": "${fileDirname}"
		},
		"problemMatcher": [
			"$gcc"
		],
		"group": {
			"kind": "build",
			"isDefault": true
		},
		"detail": "compilador: /usr/bin/clang"
	}
]
}

```
> Para Windows
- Arquivo: tasks.json
- Retirado de []()

```json

```
> Para macOS
- Arquivo launch.json
- Retirado de [https://code.visualstudio.com/docs/cpp/config-clang-mac](https://code.visualstudio.com/docs/cpp/config-clang-mac)

```json
    "version": "0.2.0",
    "configurations": [
        {
            "name": "clang - Criar e depurar o arquivo ativo",
            "type": "cppdbg",
            "request": "launch",
            "program": "${fileDirname}/${fileBasenameNoExtension}",
            "args": [],
            "stopAtEntry": false,
            "cwd": "${fileDirname}",
            "environment": [],
            "externalConsole": false,
            "MIMode": "lldb",
            "preLaunchTask": "C/C++: clang arquivo de build ativo"
        }
    ]
}
```
> Para Windows
- Arquivo launch.json
- Retirado de []()

```json
    "version": "0.2.0",
    "configurations": [
        {
            "name": "clang - Criar e depurar o arquivo ativo",
            "type": "cppdbg",
            "request": "launch",
            "program": "${fileDirname}/${fileBasenameNoExtension}",
            "args": [],
            "stopAtEntry": false,
            "cwd": "${fileDirname}",
            "environment": [],
            "externalConsole": false,
            "MIMode": "lldb",
            "preLaunchTask": "C/C++: clang arquivo de build ativo"
        }
    ]
}
```
