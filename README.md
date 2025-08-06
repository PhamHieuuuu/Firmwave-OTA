# 🚀 ESP32 OTA Firmware Update from GitHub Releases

Dự án này minh họa cách cập nhật firmware **Over-The-Air (OTA)** cho ESP32 trực tiếp từ **GitHub Releases**.

## 📌 Tính năng
- Tự động kết nối WiFi.
- Đọc **phiên bản mới nhất** từ file `version.txt` trên GitHub.
- So sánh với phiên bản đang chạy (`currentVersion`).
- Nếu có bản mới → tải file `.bin` từ GitHub Releases và ghi trực tiếp vào flash.
- **Hỗ trợ HTTP Redirect** (cần thiết cho GitHub).
- Ghi log chi tiết qua Serial để debug.

## 🛠 Cách hoạt động
1. ESP32 khởi động và kết nối WiFi.
2. Gửi HTTP GET đến **version.txt** trên GitHub (link raw).
3. Nếu `latestVersion` khác với `currentVersion` → bắt đầu OTA.
4. Sử dụng `httpUpdate.update()` để tải `.bin` từ GitHub Releases.
5. Ghi firmware mới vào phân vùng flash OTA.
6. Reset và chạy bản mới.

## ✍️ Được phát triển bởi: PhamHieuu
📅 OTA Update System 2025
