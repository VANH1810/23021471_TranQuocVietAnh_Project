# AZ TANK GAME: HUNT OR BE HUNTED!

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
  <a href="https://youtu.be/xeMLchz6kTk?si=QTepSCeT2jgIs8z_">
    <img src="https://github.com/VANH1810/23021471_TranQuocVietAnh_Project/blob/2698191432ae67ad6faf12e42b4962d41951d35d/assets/PlayScreen/StartScreen2.png" alt="AZ TANK GAME: HUNT OR BE HUNTED!">
  </a>
</p>
<p align="center">A demo run of the game (Click on the image above)</p>

### Built With

[SDL2](https://www.libsdl.org/) và [C++](https://en.wikipedia.org/wiki/C%2B%2B)

<p align="right">(<a href="#readme-top">back to top</a>)</p>

## 2. Các điểm nổi bật trong Game
* Xây dựng đạn tên lửa đuổi [Rocket](../ECS/RocketComponent.hpp), tìm đường đi ngắn nhất bằng **Thuật toán BFS, Thuật toán A*** và xây dựng lại đường sử dụng **Linked List**.
* Tính năng đạn nảy [Bullet](../ECS/BulletComponent.hpp), bằng tính toán vật lý có thể khiến đạn nảy khi gặp phải vật cản.
* Xây dựng [ECS - Entity Component System](../ECS).
* Xử lý Animation khi bắn đạn, Tính toán quy tắc di chuyển vật lý của nhân vật, Xử lý va chạm, Xử lý nhặt các túi đạn, Chuyển giao giữa các loại đạn. 
* Tự học và xử lý: **hình ảnh, âm thanh, nhạc nền, texture, text, ...** bằng thư viện khác của SDL2 như **SDL2_image, SDL2_mixer, SDL2_ttf**.
* Sử dụng đa dạng các cấu trúc dữ liệu **Vector, Map, Unordered_map, Queue, Priority Queue, ...**.
* Sử dụng được Con trỏ, Class, Struct, Hàm, ... và áp dụng được những kiến thức học được trong lớp.
* Game xây dựng hình ảnh menu, bản đồ, nhân vật đẹp và bắt mắt. Âm thanh sống động.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

## 3. Tham khảo

Mã nguồn mở:
* C++ nlohmann/json: [json.hpp](https://github.com/nlohmann/json)
* Thư viện SDL2: [SDL2](https://github.com/libsdl-org)

Nguồn học liệu tham khảo:
* [ECS.hpp](../ECS/ECS.hpp): [Entity Component System in C++ & SDL2 Tutorial](https://youtu.be/XsvI8Sng6dk?si=P7hOq0MlMJT73rH6)
* Load map: [Tile Map & Tile Set implementation SDL2 Tutorial](https://youtu.be/FQOiFUl93lI?si=LVfmj7lZTyICDGDT)

Hình ảnh:
* Bản đồ, xe tank: [TANK GAME](https://zintoki.itch.io/ground-shaker)
* Màn hình menu: [Play Screen](https://www.pixel4k.com/world-of-tanks-pixels-24151.html)
* Icon túi đạn: [BulletIcon](https://www.iconfinder.com/icons)
* Đạn: [Fire Shots](https://free-game-assets.itch.io/free-2d-tank-game-assets)

Âm nhạc:
* Nhạc nền, nhạc chiến thắng: [Music](https://danistob.itch.io/sci-fi-adventure-music-pack)
* Tiếng đạn: [Fire Sound Effect](https://mixkit.co/free-sound-effects/tanks/)
<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- CONTACT -->
## 4. Liên hệ

* Facebook: [Tran Quoc Viet Anh](https://www.facebook.com/quocvietanh.tran/)
* SĐT: 0981 181 005
* Email: tqvabk24@gmail.com
* My github: [https://github.com/VANH1810](https://github.com/VANH1810)

<p align="right">(<a href="#readme-top">back to top</a>)</p>
