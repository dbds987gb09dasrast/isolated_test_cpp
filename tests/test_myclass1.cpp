// ============================================================
//  MyClass1 のテスト（配布しない。mylib_static.lib にリンク）
//  - 内部ヘッダ MyClass1_impl.h を直接 include することで、
//    旧 private のメンバ関数・変数も普通のメンバとして検証。
//  - フレームワーク非依存で示すため CHECK を自作しているが、
//    GoogleTest / Catch2 等に置き換えても構造は同じ。
// ============================================================
#include "../src/MyClass1_impl.h"   // 内部ヘッダ（src/ を include パスに足しても良い)
#include <cstdio>

static int g_failed = 0;
#define CHECK(expr)                                                    \
    do {                                                               \
        if (expr) { std::printf("  [OK]   %s\n", #expr); }             \
        else      { std::printf("  [FAIL] %s\n", #expr); ++g_failed; } \
    } while (0)

// ご希望の TestMyClass1 形式のテストドライバ
class TestMyClass1 {
    mylib::detail::MyClass1Impl impl_;   // Impl を直接インスタンス化できる
public:
    // private だった clamp() の個別検証
    void test_clamp() {
        std::printf("test_clamp:\n");
        CHECK(impl_.clamp(-5)  == 0);    // 下限
        CHECK(impl_.clamp(0)   == 0);    // 境界
        CHECK(impl_.clamp(50)  == 50);   // 通常値
        CHECK(impl_.clamp(100) == 100);  // 境界
        CHECK(impl_.clamp(999) == 100);  // 上限
    }

    // private だったメンバ変数 total_ を直接観測しながら検証
    void test_addScore() {
        std::printf("test_addScore:\n");
        impl_.total_ = 0;                // 内部状態を直接セットアップ
        impl_.addScore(30);
        CHECK(impl_.total_ == 30);       // 内部状態を直接観測
        impl_.addScore(-10);             // clamp されて 0 加算のはず
        CHECK(impl_.total_ == 30);
        impl_.addScore(500);             // clamp されて 100 加算のはず
        CHECK(impl_.total_ == 130);
        CHECK(impl_.total() == 130);
    }
};

// 配布ヘッダ経由（=ユーザー視点）の疎通テスト
static void test_public_api() {
    std::printf("test_public_api:\n");
    mylib::MyClass1 obj;
    obj.addScore(70);
    obj.addScore(200);   // -> +100
    CHECK(obj.total() == 170);
}

int main() {
    TestMyClass1 tt;
    tt.test_clamp();
    tt.test_addScore();
    test_public_api();

    std::printf("%s (failed: %d)\n", g_failed == 0 ? "ALL PASSED" : "FAILED", g_failed);
    return g_failed == 0 ? 0 : 1;
}
