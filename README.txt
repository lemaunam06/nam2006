# README - Game SpaceShip War

## Thông Tin Tác Giả
- Họ và tên: Lê Mậu Nam  
- Mã sinh viên: 24020243  

## Giới Thiệu Về Game
Game dựa trên ý tưởng của game bắn gà. Trong game, người chơi điều khiển tàu vũ trụ tránh chướng ngài vật và tiêu diệt kẻ địch. Khi hạ Boss cuối màn, người chơi sẽ giành chiến thắng.

## Ngưỡng Điểm Mong Muốn
- Điểm: ≥9
- **Lý do**:
  - Dành nhiều thời gian tự học và phát triển game.
  - Game tích hợp các tính năng:
    - Hiển thị âm thanh, nhạc nền, texture, hoạt hình, font chữ.
    - Hệ thống high score.
    - Nhiều đối tượng game với chuyển động đa dạng và mượt mà.
    - Cấu trúc game rõ ràng, dễ hiểu.

## Nguồn Tham Khảo
- **Trang Web**: [Phát Triển Phần Mềm 123AZ](https://phattrienphanmem123az.com/lap-trinh-game-c-p2)
- **Kênh YouTube**: Phát Triển Phần Mềm 123 A-Z
- **Nguồn Ảnh & Âm Thanh**: [Itch.io](https://itch.io/game-assets/free/genre-shooter/tag-space)
                            [FreeSound](https://freesound.org/search/?q=gun+shot)
- **Nguồn Font chữ: [font-Kanit](https://fonts.google.com/specimen/Kanit)
- **Video Demo Game**: [YouTube](https://youtu.be/NOwKjARQe0k)


## Hỗ Trợ Từ AI
- Debug, tăng tốc game.
- Sửa lỗi chính tả, cú pháp.
- Giải thích chức năng và cách sử dụng lệnh.
- Hướng dẫn GitHub, SDL2.
- Cung cấp build system chạy SDL2 trên Sublime Text.
- Giới thiệu tổ chức file.

## Cách Chơi
- **Chuột**: Di chuyển tàu vũ trụ.
- **Mạng sống**: 3 mạng. Mỗi lần trúng bom, trứng, đạn hoặc va chạm với vật thể -> trừ 1 mạng. Hết mạng = Thua.
- **Space (Cách)**: Bắn đạn.
- **Mục tiêu**:
  - Tránh chướng ngài vật, bắn kẻ địch.
  - Tiêu diệt nhiều kẻ địch để đạt điểm cao.
  - Hạ Boss -> Chiến thắng.

## Các Thành Phần Trong Game
- **Gà & Ong**: Kẻ địch chính, xuất hiện liên tục.
- **Bom**:
  - **Bom1**: Rơi chậm, có thể bắn phá.
  - **Bom2**: Rơi nhanh dần, không thể bắn phá.
- **Trứng**: Xuất hiện từ gà & ong, chỉ có thể né.
- **Boss**: Xuất hiện sau một thời gian, cần nhiều đạn tiêu diệt.
- **Vật phẩm nâng cấp đạn**: Tăng tốc đạn, nâng cấp đạn (Đối đa: đạn cấp 3).

Cấu trúc của project game:

SpaceShipWar/  
│── Game/                     # Thư mục chứa tài nguyên và file chạy game  
│   ├── assets/               # Chứa tất cả hình ảnh, âm thanh, font chữ của game  
│   ├── game.exe              # File chạy game  
│   ├── highscore.txt         # Lưu điểm số cao nhất của người chơi  
│  
│── include/                  # Thư mục chứa các file header  
│   ├── background.h          # Xử lý background  
│   ├── bee.h                 # Xử lý ong  
│   ├── bom.h                 # Xử lý bom  
│   ├── boss.h                # Xử lý boss  
│   ├── bullet.h              # Xử lý đạn  
│   ├── chicken.h             # Xử lý gà  
│   ├── collision.h           # Xử lý va chạm giữa các nhân vật  
│   ├── game.h                # Khởi tạo SDL và màn hình chờ  
│── src/                      # Thư mục chứa các file định nghĩa  
│   ├── background.cpp  
│   ├── bee.cpp  
│   ├── bom.cpp  
│   ├── boss.cpp  
│   ├── bullet.cpp  
│   ├── chicken.cpp  
│   ├── collision.cpp  
│   ├── game.cpp  
│   ├── main.cpp  
│  
│── Makefile                  # File build game  
│── README.txt                # File giới thiệu game  
│── sdl2_build.sublime-build  # Cấu hình build trong Sublime Text  


## Hình Ảnh & Âm Thanh
- **Âm thanh**: Hiệu ứng bắn, nổ, nhạc nền sôi động.
- **Đồ họa**: 2D đơn giản (PNG, JPG).

## Yêu Cầu Hệ Thống
- Windows 64-bit.
- Microsoft Visual C++ Redistributable (Đã cài sẵn hoặc cần cài).
- Hỗ trợ OpenGL & DirectX.

## Cách Chạy Game
1. Mở thư mục game.
2. Chạy file **game.exe**.

