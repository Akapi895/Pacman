# GAME_BTL PACMAN
1. Introduction
Mã sinh viên: 23021709 - Phạm Anh Tuấn
Người chơi sẽ nhập vai thành cậu bạn Pacman để thu thập các dot để qua màn, với những lựa chọn độ khó khác nhau, hãy giữ tập trung cao độ nhất có thể để giành được điểm cao và ghi tên mình vào Bảng xếp hạng nhé!

2. Description

a) Entities
 - Pacman là nhân vật chính của trò chơi. Pacman có thể di chuyển theo 4 hướng trái/phải/lên/xuống.
 - Pac dot: các đối tượng mà Pacman phải ăn hết trước thời gian định sẵn để có thể qua level.
 - Big pac dot: tương tự như pac dot nhưng được nhiều điểm hơn.
 - Villians: đối tượng mà Pacman phải tránh, nếu va phải sẽ bị mất đi 1 điểm sinh mạng.
 - Brick: đối tượng mà cả Pacman hay Pac pac đều không thể đi qua (map).
b) Game play, collision and explosion
- Nhiệm vụ:
+ Điều khiển Pacman di chuyển qua mê cung và ăn hết tất cả Pac-Dot và Big Pac-Dot trong thời gian quy định (5 phút).
+ Tránh va chạm với những Villian, mỗi lần va chạm sẽ khiến bạn mất đi một mạng quý giá.
+ Di chuyển Pacman một cách thông minh qua những mê cung ngày càng phức tạp khi bạn tiến lên các cấp độ cao hơn.
- Cơ chế trò chơi:
+ Mỗi cấp độ mang đến một bố cục mê cung độc đáo với độ khó khác nhau.
+ Thời gian là yếu tố then chốt, hãy tận dụng từng bước di chuyển và tránh lãng phí những giây phút quý báu.
+ Pacman có 3 mạng cho mỗi trò chơi; hãy sử dụng chúng một cách khôn ngoan để chinh phục mê cung.
c) Độ khó của game cũng được phân chia thành 4 mức độ:
- Mức 1 (Easy): Với mức độ chơi này, tất cả các con Pac pac đều di chuyển 1 cách ngẫu nhiên, không có quy luật nào.
- Mức 2 (Normal): Ở mức kế tiếp, đôi khi những con Pac pac có thể xác định được vị trí của người chơi và đuổi theo, tuy nhiên điều đó chỉ xảy ra trong thời gian ngắn và ngắt quãng.
- Mức 3 (Hard): Cấp độ chơi này, những con Pac pac sẽ đuổi theo bạn thường xuyên hơn so với mức độ 2.
- Mức 4 (Very hard): Ở mức độ cuối cùng, những con Pac pac sẽ liên tục tìm và đuổi theo bạn nhiều nhất, nhanh nhất và tối ưu nhất có thể, chúng có thể đuổi theo liên tục hoặc chặn cả 2 đầu lối đi nhân vật của bạn.
3. Controls and Options
Control	Key
UP	   W
DOWN	 S
LEFT	 A
RIGHT	D

Option	Key
New Game	Ctrl + N
Pause	   SPACE
Resume	  SPACE
5. Mẹo thành công:
- Lập kế hoạch di chuyển cẩn thận để giảm thiểu ngõ cụt và tối đa hóa hiệu quả.
- Giữ tập trung và tỉnh táo, vì tốc độ sẽ tăng dần với mỗi cấp độ.
# Hãy chinh phục thử thách và trở thành bậc thầy Pacman!
