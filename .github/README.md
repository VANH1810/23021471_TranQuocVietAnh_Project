# AZ TANK GAME: HUNT OR BE HUNTED!
Bài tập lớn lớp Lập trình nâng cao **2324II_INT2215_22** - **K68CA1**

## **Họ và tên: [Trần Quốc Việt Anh](https://github.com/VANH1810)** / **Mã số sinh viên: 23021471**


<div id="readme-top"></div>
<!-- TABLE OF CONTENTS -->

## Mục lục

<details>
  <ol>
    <li>
      <a href="#1-Giới-thiệu-chung">Giới thiệu chung</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li><a href="#2-ngưỡng-điểm-mong-muốn-9---10">Ngưỡng điểm mong muốn</a></li>
    <li>
      <a href="#3-Các-điểm-nổi-bật-trong-Game">Các điểm nổi bật trong Game</a>
    </li>
    <li><a href="#4-Tham-khảo">Tham khảo</a></li>
    <li><a href="#5-Liên-hệ">Liên hệ</a></li>
  </ol>
</details>

<!-- GENAERAL INFORMATION -->
## 1. Giới thiệu chung
AZ là một trò chơi 3 người chơi tuyệt vời cũng có thể được chơi ở hai người chơi và mục tiêu là đi lang thang, đi bộ và bắn và càn quét tất cả các đối thủ, càng sớm càng tốt,

Bạn sẽ thấy mình trong một mê cung với xe tăng của bạn và các chiếc xe tăng của kẻ thù.
Bạn phải sử dụng các nút định hướng để di chuyển xe tăng của bạn (tiến, lùi, quay trái và quay phải). Bắn phát súng của bạn bằng nút bắn.

Hãy làm chủ nghệ thuật ricochets – những cú đánh của bạn có thể bật ra khỏi tường và khiến đối thủ mất cảnh giác. Tiếp tục di chuyển để tránh đạn lạc.

<p align="center">
  <a href="https://youtu.be/ZCdxY4nwDTw">
    <img src="https://github.com/VANH1810/23021471_TranQuocVietAnh_Project/blob/bcf24f98ec9cf39b7e1330987cf96fd8172d23c9/assets/PlayScreen/StartScreen.png" alt="AZ TANK GAME: HUNT OR BE HUNTED!">
  </a>
</p>
<p align="center">A demo run of the game</p>

### Built With

[SDL2](https://www.libsdl.org/) và [C++](https://en.wikipedia.org/wiki/C%2B%2B)

<p align="right">(<a href="#readme-top">back to top</a>)</p>

## 2. Ngưỡng điểm mong muốn: 9 - 10
Với quá trình làm bài tập nỗ lực và không ngừng học hỏi của mình, em mong muốn ngưỡng điểm mình đạt được sẽ là 9 - 10đ.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

## 3. Các điểm nổi bật trong Game
* Xây dựng đạn tên lửa đuổi [Rocket](../ECS/RocketComponent.hpp), tìm đường đi ngắn nhất bằng **Thuật toán BFS, Thuật toán A*** và cấu trúc **Linked List**.
* Tính năng đạn nảy [Bullet](../ECS/BulletComponent.hpp), bằng tính toán vật lý có thể khiến đạn nảy khi gặp phải vật cản.
* Xây dựng [ECS - Entity Component System](../ECS).
* Xây dựng được bản đồ mê cung phức tạp và kiểm tra vật cản.
* Xử lý Animation khi bắn đạn, Xử lý va chạm, Xử lý di chuyển quay của nhân vật, Xử lý nhặt các túi đạn, Chuyển giao giữa các loại đạn. 
* Tự học và xử lý: **âm thanh, nhạc nền, texture, text, ...** bằng thư viện khác của SDL2 như **SDL2_image, SDL2_mixer, SDL2_ttf**.
* Sử dụng đa dạng các cấu trúc dữ liệu **Vector, Map, Unordered_map, Queue, Priority Queue, ...**.
* Sử dụng được Con trỏ, Class, Struct, Hàm, ... và áp dụng được nhiều kiến thức học được trong lớp.
* Game xây dựng hình ảnh menu, bản đồ, nhân vật đẹp và bắt mắt. Âm thanh sống động.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

## 4. Tham khảo
Mã nguồn mở:
* C++ nlohmann/json: [json.hpp](https://github.com/nlohmann/json)
* Thư viện SDL2: [SDL2](https://github.com/libsdl-org)

Nguồn học tham khảo:
* [ECS.hpp](../ECS/ECS.hpp): [Entity Component System in C++ & SDL2 Tutorial](https://youtu.be/XsvI8Sng6dk?si=P7hOq0MlMJT73rH6)
* Load map: [Tile Map & Tile Set implementation SDL2 Tutorial](https://youtu.be/FQOiFUl93lI?si=LVfmj7lZTyICDGDT)

Hình ảnh:
* Bản đồ, xe tank: [TANK GAME](https://zintoki.itch.io/ground-shaker)
* Icon túi đạn: [BulletIcon](https://www.iconfinder.com/icons)
* Đạn: [Fire Shots](https://free-game-assets.itch.io/free-2d-tank-game-assets)

Âm nhạc:
* Nhạc nền, nhạc chiến thắng: [Music](https://danistob.itch.io/sci-fi-adventure-music-pack)
* Tiếng đạn: [Fire Sound Effect](https://mixkit.co/free-sound-effects/tanks/)
<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- CONTACT -->
## 5. Liên hệ

* Facebook: [Tran Quoc Viet Anh](https://www.facebook.com/quocvietanh.tran/)
* SĐT: 0981 181 005
* Email: tqvabk24@gmail.com
* My github: [https://github.com/VANH1810](https://github.com/VANH1810)

<p align="right">(<a href="#readme-top">back to top</a>)</p>
