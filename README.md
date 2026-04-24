針對 **`basic-05-unit-advertising-connection` (BLE 廣播機制與連線流程)** 單元，這是學員從「有線控制」轉向「無線物聯網 (IoT)」的物理與邏輯門檻。它要求學員具備 **事件驅動編程 (Event-Driven Programming)** 的思維，學習設備如何宣告自身身份、如何透過硬體（如 LED）即時反映連線狀態，以及如何將抽象的信號強度 (RSSI) 轉化為具備感知能力的 **「近場偵測」** 應用。

以下是在 **GitHub Classroom** 部署其作業 (Assignments) 的具體建議：

### 1. 範本倉庫 (Template Repo) 配置建議
BLE 作業的核心在於「狀態管理」與「無線感知」，範本應包含完整的 BLE 框架，建議包含：
*   **📂 `src/main.cpp`**：**回呼函數 (Callbacks) 實作區**。學員需在此繼承並實作 `BLEServerCallbacks` 類別，補全 `onConnect` 與 `onDisconnect` 邏輯，特別是斷開後的 **「自動重啟廣播」** 機制。
*   **📂 `include/ble_identity.h`**：引腳與標識定義中心。提供宏定義供學員填寫自定義的 `DEVICE_NAME`（要求包含座號）與 `SERVICE_UUID`。
*   **📂 `README.md`**：**無線實驗報表**。提供表格範本讓學員記錄：「距離 (cm)」 vs 「RSSI 平均值 (dBm)」。並貼上掃描工具（如 nRF Connect）偵測到自身設備的截圖。
*   **📂 `docs/STATE_MACHINE.md`**：**生命週期說明書**。要求學員以文字描述 BLE 設備從「廣播 -> 被發現 -> 連線 -> 斷開 -> 重新廣播」的狀態轉換過程。

---

### 2. 作業任務部署細節

#### 任務 1：「改名大師」自定義廣播封包 (Name Master Lab)
*   **目標**：建立對 BLE 身份宣告 (Advertising) 的直覺，學會使用專業偵錯工具驗證無線資產。
*   **Classroom 部署建議**：
    *   **唯一性挑戰**：要求學員修改名稱為 `Vibe-Student-XX` (XX 為座號)。
    *   **封包審計**：使用手機 APP 掃描並回傳該設備的 MAC 地址。
    *   **驗證要點**：README 中必須清楚標註 MAC 地址與對應的 Service UUID。這是證明學生能「正確宣告存在」的第一步。

#### 任務 2：「連線守門員」Server 回呼機制 (Connection Guard Lab)
*   **目標**：掌握異步事件處理，確保系統具備硬體層級的狀態回饋與故障恢復能力 (Self-healing)。
*   **Classroom 部署建議**：
    *   **狀態同步顯像**：連線時，板載 LED 恆亮綠燈；斷線時，LED 閃爍。
    *   **魯棒性 (Robustness) 實作**：**核心考點**。學員必須在 `onDisconnect` 回呼中加入 `pServer->startAdvertising()`。
    *   **驗證要點**：測試「連線後再斷開」，手機是否能立即再次搜尋到該設備？（若無法搜尋即代表未實作重啟機制）。

#### 任務 3：「距離強度」RSSI 測距實驗 (RSSI Distance Lab)
*   **目標**：體會無線信號隨物理空間衰減的非線性規律，實作基於信號強度的「空間交互」。
*   **Classroom 部署建議**：
    *   **數據採樣量測**：分別在 10cm, 50cm, 150cm 處記錄 10 組 RSSI 平均值。
    *   **近場提示 (Proximity Recall)**：撰寫邏輯，當 RSSI 大於 `-50dBm` 時（代表極近距離），觸發 LED 快速閃爍作為感知互動。
    *   **驗證要點**：在報告中描述：為何手機放很近時 RSSI 是 -40 而非 0？並說明遮擋物（如手掌）對 RSSI 的影嚮。

---

### 3. 無線通訊與生命週期點評標準 (Wireless Lifecycle & UX Standards)
此單元的價值在於 **「對無線物理特性的掌握與連線魯棒性的設計」**：
*   [ ] **連線自癒能力**：斷開連線後，設備是否能不需要重開機就自動重新進入廣播模式？
*   [ ] **硬體同步意識**：LED 的視覺回饋是否精準對應了藍牙內部的狀態機 (State Machine)？
*   [ ] **信號洞察力**：RSSI 實驗日誌是否呈現出了信號隨距離增加而對數衰減的趨勢？

### 📁 推薦範本結構 (GitHub Classroom Template)：
```text
.
├── src/main.cpp         # 核心：BLE Server 回呼邏輯與 RSSI 閾值處理
├── include/ble_app.h    # 配置：UUID 產生器與設備名稱 Macro 定義
├── docs/LifeCycle.png   # 文檔：學員繪製的 BLE 連線生命週期流程圖
├── README.md            # 總結：我如何透過 RSSI 建立空間感知並確保連線韌性
└── assets/nrf_scan.jpg  # 照片：手機 App 成功掃描到自定義封包的證據截圖
```

透過這種部署方式，學生能體驗到 **「好的物聯網工程師，是能將看不見的無線電波轉化為可視化的硬體行為，並在混亂的頻段中為設備建立起穩健通訊協定的系統設計師」**。掌握廣播與連線機制後，學員將擁有了開發「智慧 Beacon、近場支付感應、自動解鎖門禁」最核心也最具未來感的無線開發能力！_

---

## 🛠 學員實驗報表 (Student Lab Report)

### 1. 設備基本資訊
*   **自定義名稱 (Device Name)**: `Vibe-Student-XX`
*   **MAC 位址**: `[在此填入你的設備 MAC 地址]`
*   **Service UUID**: `4fafc201-1fb5-459e-8fcc-c5c9c331914b`

### 2. RSSI 距離測量實驗 (Task 3)
請在不同距離下測量 10 組 RSSI 並取其平均值：

| 距離 (cm) | RSSI 平均值 (dBm) | 備註 (是否有遮擋物) |
| :--- | :--- | :--- |
| 10 cm | | |
| 50 cm | | |
| 150 cm | | |

### 3. 生命週期觀察 (Task 2)
*   **斷開連線後的行為**: [描述手機斷開後，板子 LED 的變化以及手機是否能立即重新掃描到設備]

### 4. 實驗截圖
請將 `nRF Connect` 或相關掃描工具的截圖存放在 `assets/nrf_scan.jpg` 並在此連結：
![Scan Screenshot](assets/nrf_scan.jpg)

### 5. 心得與發現
[在此描述你對 RSSI 隨距離衰減的觀察，以及為何遮擋物會影嚮信號強度]
