# GAME_BTL PACMAN
**1. Giới thiệu**

Mã sinh viên: _23021709_ - Phạm Anh Tuấn

Người chơi sẽ nhập vai thành cậu bạn Pacman để thu thập các dot để qua màn, với những lựa chọn độ khó khác nhau, hãy giữ tập trung cao độ nhất có thể để giành được điểm cao và ghi tên mình vào Bảng xếp hạng nhé!

**2. Hướng dẫn tải game**

- Tại phần "Code" chọn "Download ZIP".
- Sau khi tải về, giải nén và mở file pacman.cbp.
- Nhấn F9 (Fn + F9) để chơi.

_Lưu ý:_ Nếu không chơi được, hãy thử thay thế các file SDL có sẵn thành các file SDL tự tải về.

**3. Mô tả chi tiết**

**a) Các nhân vật**

 - Pacman là nhân vật chính của trò chơi. Pacman có thể di chuyển theo 4 hướng trái/phải/lên/xuống.
 - Pac dot: các đối tượng mà Pacman phải ăn hết trước thời gian định sẵn để có thể qua level.
 - Big pac dot: tương tự như pac dot nhưng được nhiều điểm hơn.
 - Villians: đối tượng mà Pacman phải tránh, nếu va phải sẽ bị mất đi 1 điểm sinh mạng.
 - Brick: đối tượng mà cả Pacman hay Villians đều không thể đi qua (map).
   
**b) Nhiệm vụ, cơ chế trò chơi**

_Nhiệm vụ:_

 + Điều khiển Pacman di chuyển qua mê cung và ăn hết tất cả các dot trong thời gian quy định (200s).
 + Tránh va chạm với Villians, mỗi lần va chạm sẽ khiến bạn mất đi một mạng quý giá.
 + Di chuyển Pacman một cách thông minh qua những mê cung ngày càng phức tạp khi bạn tiến lên các cấp độ cao hơn.

_Cơ chế trò chơi:_

 + Mỗi cấp độ mang đến một bố cục mê cung độc đáo với độ khó khác nhau.
 + Thời gian là yếu tố then chốt, hãy tận dụng từng bước di chuyển và tránh lãng phí những giây phút quý báu.
 + Pacman có 3 mạng cho mỗi trò chơi; hãy sử dụng chúng một cách khôn ngoan để chinh phục mê cung.

**c) Độ khó:**

_Game được chia thành 4 mức độ khó khác nhau:_

- Mức 1 (Easy): Với mức độ chơi này, tất cả Villians đều di chuyển 1 cách ngẫu nhiên, không có quy luật nào.
- Mức 2 (Normal): Ở mức kế tiếp, đôi khi Villians có thể xác định được vị trí của người chơi và đuổi theo, tuy nhiên điều đó chỉ xảy ra trong thời gian ngắn và ngắt quãng.
- Mức 3 (Hard): Cấp độ chơi này, Villians sẽ đuổi theo bạn thường xuyên hơn so với mức độ 2.
- Mức 4 (Very hard): Ở mức độ cuối cùng, Villians sẽ liên tục tìm và đuổi theo bạn nhiều nhất, nhanh nhất và tối ưu nhất có thể, chúng có thể đuổi theo liên tục hoặc chặn cả 2 đầu lối đi nhân vật của bạn.

**4. Thao tác phím**

![asdw](https://github.com/Akapi895/game_btl/assets/83953516/71f80dc2-a664-478b-b4e8-8e6ef799ac26)
![pause](https://github.com/Akapi895/game_btl/assets/83953516/92064709-8b32-4f91-b693-237dfc8098ec)

**5. Mẹo để giành chiến thắng:**

- Lập kế hoạch di chuyển cẩn thận để giảm thiểu ngõ cụt và tối đa hóa hiệu quả.
- Độ khó càng cao, điểm tính cho các big pac dot càng nhiều.
- Giữ tập trung và tỉnh táo, vì tốc độ sẽ tăng dần với mỗi cấp độ.

## Hình ảnh minh họa
**Menu**

![menu pacman](https://github.com/Akapi895/game_btl/assets/83953516/63819ef7-42b6-4d8b-a40a-d7e462e9c6d3)

**Background game**

![background](https://github.com/Akapi895/game_btl/assets/83953516/dc1f3767-7d2b-4f6d-b1c2-d11ec996bb29)

**Game win**

![backgroundWinGame](https://github.com/Akapi895/game_btl/assets/83953516/ebf28bf4-9736-42fc-a7bb-f34fc6c5f2da)

**Game lost**

![backgroundLostGame](https://github.com/Akapi895/game_btl/assets/83953516/1d9e2a05-7a2c-4c26-91b0-a83b575df7b1)


## Kiến thức đã sử dụng
- Thư viện SDL 2.0
- Kỹ thuật đọc ghi file
- Lưu lại điểm số
- Chia file thành các header để thuận tiện cho việc quản lý
- Tile map, fps...
- Các kiến thức về mảng, set, queue, stack...
- Struct, class
- Xác suất thống kê
- Thuật toán A*

## Nguồn tham khảo
- https://wiki.libsdl.org/SDL2/Tutorials (tìm hiểu về thư viện SDL 2.0)
- https://www.youtube.com/playlist?list=PLNOBk_id22bw6LXhrGfhVwqQIa-M2MsLa (học về các kỹ thuật cơ bản như nhân vật, xử lý va chạm...)
- Tài liệu của thầy Hiếu, cô Châu
- https://rosettacode.org/wiki/ (học thuật toán A*)
- Nhạc nền: Dragon ball
- Hình ảnh: Tự thiết kế, https://opengameart.org/...
