1. 2 cach de cai openssl
    - 1 la tai msi ncc ben thu 3 (easy): https://slproweb.com/products/Win32OpenSSL.html
    - 2 la tai file nen (trang goc deo co build san, phai tai file ve  build dit cu):   https://www.openssl.org/

2. Cach 1 thi de roi. Thu lam cach 2
    - De build duoc Openssl, ca nhieu thu, compiler cho c va cho binary. 
        tai perl strawberry
        NASM cho binary build, sau khi da cai` perl, va NASM
        1. Mo cmd cho Visual Studio (developer command prompt)
        2. perl configure -> VC-WIN64A (doi tuong cai` dat cho)
        3. Xac dinh duoc doi tuong -> bat dau cai dat: perl configure VC-WIN64A --openssldir=C:\OpenSSL-Win64 --prefix=C:\OpenSSL-Win64
        4. xong buoc 3 -> thuc hien : nmake -> biên dịch và xây dựng
        5. xong buoc 4 -> thuc hien : nmake install -> để install các binary