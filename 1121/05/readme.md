# 🎮 C\# 스크립트 입문을 위한 Unity 기초 (GameObject & Script)

## 🛠️ 개발 환경 및 준비

  * **Unity 버전:** 2021.3.6f1 LTS (문서 기준)
  * **프로젝트 생성:** 3D 코어 템플릿으로 `GameObjectTest` 프로젝트 생성

## 🏗️ 1. 기본 스테이지 및 오브젝트 구성

| 단계 | 오브젝트 | 주요 작업 |
| :--- | :--- | :--- |
| **스테이지** | **Cube** → `Ground` | 바닥 오브젝트 생성 및 **Scale** (예: X=10, Y=0.1, Z=10) 조정. 새로운 **Material** 생성 후 적용. |
| **플레이어** | **Sphere** → `Ball` | 공 오브젝트 생성 및 **Rigidbody** 컴포넌트 추가 (중력 및 물리 작용 활성화). |
| **조명** | **Directional Light** | 기본 조명 확인 및 필요시 조정. |

## 💻 2. C\# 스크립트의 기본 구조

C\# 스크립트는 **`MonoBehaviour`** 클래스를 상속받으며, 주로 다음 함수들을 사용하여 게임 로직을 구현합니다.

### 📌 핵심 기본 함수

| 함수 | 실행 시점 | 용도 |
| :--- | :--- | :--- |
| **`void Start()`** | 스크립트가 활성화될 때 **단 한 번** 호출됨. | 초기 설정 및 초기화 작업 (예: 초기 위치 설정, 컴포넌트 참조) |
| **`void Update()`** | 매 프레임마다 호출됨 (컴퓨터 성능에 따라 주기가 다름). | **연속적인 동작** 구현 (예: 이동, 회전, 키 입력 감지, 타이머 계산) |

**예시 코드 (`PrtPosition.cs`)**

```csharp
using UnityEngine;

public class PrtPosition : MonoBehaviour
{
    // Start() 함수 예시: 게임 시작 시 한번 호출
    void Start()
    {
        // 현재 오브젝트의 위치를 콘솔 창에 출력
        Debug.Log("Start Position: " + transform.position); 
    }

    // Update() 함수 예시: 매 프레임마다 호출
    void Update()
    {
        // If문과 Debug.Log를 사용한 조건문 실행 예시
        if (transform.position.y < 0)
        {
             Debug.Log("현재 위치는 0보다 낮습니다: " + transform.position.y);
        }
        else
        {
             Debug.Log("현재 위치는 0보다 높거나 같습니다: " + transform.position.y);
        }
    }
}
```

-----

## 🚀 3. 오브젝트 제어 및 상호작용 스크립트

### 3.1. 기본 변환(Transform) 제어

  * **`RadiusChange.cs`**: `Start()`에서 `transform.localScale`을 사용하여 공의 크기를 변경하는 예시.
  * **`BallJump.cs`**: `Update()` 내에서 **`Input.GetKeyDown(KeyCode.Space)`** 등을 사용하여 특정 키 입력 시 \*\*`Rigidbody.AddForce()`\*\*로 위쪽 방향 힘을 가해 공을 튀어 오르게 합니다.

### 3.2. 카메라 및 환경 제어

  * **`CameraFollow.cs`**: **`public Transform target;`** 변수를 선언하여 유니티 에디터에서 `Ball` 오브젝트를 연결받고, `Update()`에서 **`transform.position = target.position`** 등을 이용해 공의 위치를 따라가도록 구현합니다.
  * **`GroundMove.cs`**: `Input.GetKey()` 등을 사용하여 키 입력(예: **'W', 'A', 'S', 'D'**)을 감지하고, \*\*`transform.Translate()`\*\*를 사용하여 `Ground` 오브젝트를 이동시킵니다.

### 3.3. 충돌 감지 및 아이템 처리

| 스크립트 | 컴포넌트 설정 | 주요 로직 |
| :--- | :--- | :--- |
| **충돌** | **`Ground`** 오브젝트에 스크립트 추가 | `OnCollisionEnter(Collision other)` 함수를 사용하여 충돌 발생 시점 및 충돌한 오브젝트 정보(`other`) 출력. |
| **코인 획득** | **`Coin`** 오브젝트에 **`Is Trigger`** 체크 | `OnTriggerEnter(Collider other)` 함수를 사용하여 플레이어와의 겹침(충돌 아님)을 감지하고 코인 오브젝트를 `Destroy()`하여 제거. |
| **아이템 효과** | **`RedCoinItem`** 스크립트 | 코인 획득 시 **`GameManager`** 클래스의 변수를 참조하여 장애물을 제거하는 등 게임 내 상태를 변경하는 로직 구현. |

### 3.4. 고급 기능: 프리팹과 상속

  * **프리팹 (Prefab) 사용:** `Shooter` 스크립트에서 **`public GameObject stone;`** 변수를 선언한 후, 에디터에서 **`Stone` 프리팹**을 연결합니다.
  * **`Instantiate` 함수:** `Update()`에서 타이머 변수(`timeCount`)를 사용하여 3초마다 \*\*`Instantiate(stone, ...)`\*\*를 호출, 돌 프리팹을 생성하여 던집니다.
  * **클래스 상속:** `Shooter` 스크립트가 `ObstacleMove` 클래스를 상속받아 \*\*`base.Update()`\*\*를 호출함으로써, 부모 클래스의 움직이는 기능을 재활용하는 예시를 보여줍니다.
