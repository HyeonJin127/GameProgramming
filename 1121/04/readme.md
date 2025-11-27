# 🏃 장애물 런 게임 프로젝트 (RUN Project)

이 문서는 Unity 엔진을 사용하여 간단한 **장애물 런 게임**을 제작하는 과정을 단계별로 정리한 가이드입니다.

## ⚙️ 프로젝트 환경 및 준비

| 항목 | 내용 |
| :--- | :--- |
| **Unity 버전** | 2019.2.5f1 (테스트 완료) |
| **프로젝트 이름** | `RUN` |
| **프로젝트 종류** | 3D |
| **초기 Scene 이름** | `Main` (기존 `SampleScene`을 변경) |

## 📦 필수 에셋 임포트

Unity Asset Store에서 **`Standard Assets`**을 검색하여 임포트합니다. 불필요한 에셋을 제외하고 다음 컴포넌트만 선택하여 프로젝트에 추가합니다.

* `Cameras`
* `Characters`
* `CrossPlatformInput`
* `Prototyping`
* `Utility`

## 🏗️ 스테이지 및 환경 구성

### 1. 지형 및 장애물 배치

* **Floor (바닥):** 스테이지의 주 바닥을 구성합니다.
* **Block / BigBlock:** 캐릭터가 피해야 하는 장애물 오브젝트를 적절한 위치에 배치하고 Transform 값을 설정합니다.
* **OutArea:** 캐릭터가 바닥 아래로 떨어졌을 때 게임 오버를 처리하기 위한 영역을 만듭니다.

### 2. 배경 오브젝트

* **Wall, Pillar:** 스테이지의 배경을 구성하는 벽이나 기둥 오브젝트를 배치합니다.
* **텍스처 적용:** Asset Store에서 `Metal textures pack` 등의 에셋을 가져와 오브젝트들에 적용하여 시각적 완성도를 높입니다.

### 3. 라이트 설정

게임 분위기를 연출하기 위해 다양한 라이트를 추가하고 설정합니다.

* **Directional Light** (태양광 역할)
* **Spotlight** (특정 영역 강조)
* **Point Light** (주변을 밝히는 역할)

## 🧑 캐릭터 및 카메라 설정

### 1. 플레이어 설정

* **캐릭터 모델:** `Standard Assets` 내의 **`Third Person Controller`** 프리팹을 사용하여 **Player**를 Scene에 배치합니다.
* **태그 설정:** Player 오브젝트에 `Player` 태그를 지정합니다.

### 2. 카메라 설정

* **카메라:** `Standard Assets` 내의 **`Multipurpose CameraRig`** 프리팹을 Scene에 배치합니다.
* **스크롤 설정:** 카메라가 Player를 따라가며 게임 화면이 자동으로 스크롤되도록 설정합니다.

## 💻 게임 로직 및 UI 구현

### 1. 게임 UI 구성 (Canvas)

다음과 같은 텍스트 및 버튼 오브젝트를 **Canvas**에 구성하고 적절한 스크립트를 연결합니다.

| UI 요소 | 목적 |
| :--- | :--- |
| **TimeText** | 게임 진행 시간을 표시 |
| **ResultTitle** | 게임 결과 제목 ("게임 성공" 또는 "게임 오버") |
| **ResultTimeText** | 최종 플레이 시간 표시 |
| **BestTimeText** | 최고 기록 시간 표시 |
| **RetryButton** | 게임 재시작 버튼 |

### 2. 버튼 클릭 이벤트 연결

**`RetryButton`**에 `GameResult` 스크립트의 **`OnRetry()`** 메소드를 연결하여, 버튼 클릭 시 게임이 처음 상태로 다시 시작되도록 구현합니다.

* **연결 방법:** `Button (Script)` 컴포넌트의 `On Click()` 이벤트에 Canvas 오브젝트를 드래그하고, `GameResult` 컴포넌트의 `OnRetry()` 함수를 선택합니다.

## 🎶 사운드 추가

1.  Asset Store에서 **`Free Music Pack`** 등의 무료 사운드 에셋을 검색하여 임포트합니다.
2.  배경 오브젝트(예: `Pillar`)에 **`Audio Source`** 컴포넌트를 추가합니다.
3.  **`AudioClip`**을 선택하고, **반복 재생 (`Loop`)** 옵션을 활성화하여 게임 배경 음악으로 사용합니다.
