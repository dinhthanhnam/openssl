chi la 1 trong so cac cach lam
1. tai va cai dat msys2.
sau do mo msys2 len.
2. cai dat goi dev co ban cho developer bang pacman  trong my2
pacman -S --needed base-devel mingw-w64-ucrt-x86_64-toolchain

(gom ca gcc g++ va openssl.exe)
3. Tao bien moi truong: system variables 
add bien moi : C:\msys64\ucrt64\bin
4. vao visual va quay, add file .cpp vao , no tu goi y tai them extension (tai vao neu chua co)
5. mac dinh mo file .cpp no ko nhan compiler (deo hieu vi sao) deo quan trong, vi minh cung phai goi den compiler thu cong thoi
6. open intergrated terminal (cmd hoac powershell deu dc)
7. command prompt truoc:

    compile .cpp -> exe truoc: g++ test.cpp lcryto -o abc.exe 
    chay exe -> abc.exe

7. powershell lenh khac:

    compile .cpp -> exe truoc: g++ test.cpp lcryto -o abc.exe 
    chay exe -> .\abc.exe

dung cai nao cung duoc, ko debug mac dinh bang chuc nang debug cua vs code, deo hieu vao sao




