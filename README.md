# O que é o wellModernC

Repositório com estudos na linguagem C em ambiente Windows e macOS a fim de entender o funcionamento desta linguagem em seus dialetos e formas mais modernas. Como estou estudando mais sobre o assunto, resolvi compartilhar meus estudos e descobertas. Irei depositar aqui códigos, dicas de material didático e tutoriais de aprendizado da linguagem.

As aplicacoes presentes nesse repositório para aprendizado estarão na seção a seguir.

## Aplicações criadas

- **wellDoneServer**: servidor web simples para fins didáticos. Ele é composto pelos arquivos: **(para fazer)**.
- ...

## Autor
Wellington Wagner F. Sarmento

## Compiladores, ferramentas, instalações e configurações
- **Editor**: Visual Studio Code
- **Extensões para o Editor**: [Microsoft C/C++ Extetion Pack](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools-extension-pack), Bracket Pair Colorizer, [C/C++ Snppets (Hash)](https://marketplace.visualstudio.com/items?itemName=CoenraadS.bracket-pair-colorizer),[Code Runner (.run)](https://marketplace.visualstudio.com/items?itemName=formulahendry.code-runner)
- **Compiladores**: [clang](https://clang.llvm.org/get_started.html) ou [gcc for Windows](https://gcc.gnu.org/install/binaries.html)
- **Depurador**: lldb ou gdb
- **Documentação**: [Doxygen](https://www.doxygen.nl/download.html), [tutorial do doxygen](https://moodle.ufsc.br/pluginfile.php/2377678/mod_resource/content/0/DoxygenTutorial.pdf)
- **Instalações**
> Para macOS

> Para Windows

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
- Retirado de [https://code.visualstudio.com/docs/cpp/config-mingw](https://code.visualstudio.com/docs/cpp/config-mingw)

```json
{
  "tasks": [
    {
      "type": "cppbuild",
      "label": "C/C++: g++.exe build active file",
      "command": "C:/msys64/mingw64/bin/g++.exe",
      "args": ["-g", "${file}", "-o", "${fileDirname}\\${fileBasenameNoExtension}.exe"],
      "options": {
        "cwd": "${fileDirname}"
      },
      "problemMatcher": ["$gcc"],
      "group": {
        "kind": "build",
        "isDefault": true
      },
      "detail": "compiler: C:/msys64/mingw64/bin/g++.exe"
    }
  ],
  "version": "2.0.0"
}
```
> Para macOS
- Arquivo launch.json
- Retirado de [https://code.visualstudio.com/docs/cpp/config-clang-mac](https://code.visualstudio.com/docs/cpp/config-clang-mac)

```json
{
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
- Retirado de [https://code.visualstudio.com/docs/cpp/config-mingw](https://code.visualstudio.com/docs/cpp/config-mingw)

```json
{
  "version": "0.2.0",
  "configurations": [
    {
      "name": "g++.exe - Build and debug active file",
      "type": "cppdbg",
      "request": "launch",
      "program": "${fileDirname}\\${fileBasenameNoExtension}.exe",
      "args": [],
      "stopAtEntry": false,
      "cwd": "${fileDirname}",
      "environment": [],
      "externalConsole": false,
      "MIMode": "gdb",
      "miDebuggerPath": "C:\\msys64\\mingw64\\bin\\gdb.exe",
      "setupCommands": [
        {
          "description": "Enable pretty-printing for gdb",
          "text": "-enable-pretty-printing",
          "ignoreFailures": true
        }
      ],
      "preLaunchTask": "C/C++: g++.exe build active file"
    }
  ]
}
```
