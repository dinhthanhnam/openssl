@echo off
rem Thiết lập biến môi trường cho OpenSSL
set PATH=%PATH%;C:\OpenSSL-Win64\bin

rem Chạy lệnh configure để cấu hình OpenSSL
perl configure VC-WIN64A --openssldir=C:\OpenSSL-Win64 --prefix=C:\OpenSSL-Win64

rem Biên dịch OpenSSL bằng nmake
nmake

rem Cài đặt OpenSSL vào thư mục cài đặt
nmake install

echo OpenSSL đã được cài đặt thành công.
