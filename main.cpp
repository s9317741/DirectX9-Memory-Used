#include <d3d9.h>
#include <stdio.h>
#include <windows.h>
#include <tchar.h>

#pragma comment(lib, "d3d9.lib")

int main()
{

    // 创建窗口...
    HINSTANCE hInstance = GetModuleHandle(NULL);
    HWND hWnd = CreateWindowEx(0, _T("MyWindowClass"), _T("My Window"), WS_OVERLAPPEDWINDOW, 0, 0, 640, 480, NULL, NULL, hInstance, NULL);
    if (hWnd == NULL)
    {
        // 窗口创建失败
        return -1;
    }

    IDirect3D9* pD3D = Direct3DCreate9(D3D_SDK_VERSION);
    if (!pD3D)
    {
        printf("Failed to create IDirect3D9 object.\n");
        return -1;
    }

    D3DADAPTER_IDENTIFIER9 adapterId;
    ZeroMemory(&adapterId, sizeof(D3DADAPTER_IDENTIFIER9));
    if (FAILED(pD3D->GetAdapterIdentifier(D3DADAPTER_DEFAULT, 0, &adapterId)))
    {
        printf("Failed to get adapter identifier.\n");
        return -1;
    }

    //printf("DedicatedVideoMemory: %u bytes\n", pD3D->GetAvailableTextureMemory());

    D3DDEVTYPE deviceType = D3DDEVTYPE_HAL; // 使用硬件渲染
    D3DCAPS9 caps;
    ZeroMemory(&caps, sizeof(D3DCAPS9));
    if (FAILED(pD3D->GetDeviceCaps(D3DADAPTER_DEFAULT, deviceType, &caps)))
    {
        printf("Failed to get device caps.\n");
        return -1;
    }

    D3DPRESENT_PARAMETERS presentParams = {};
    presentParams.Windowed = TRUE; // 是否窗口化
    presentParams.SwapEffect = D3DSWAPEFFECT_DISCARD; // 交換鏈效果
    presentParams.BackBufferFormat = D3DFMT_UNKNOWN; // 後緩衝區格式
    presentParams.BackBufferCount = 1; // 後緩衝區數量
    presentParams.EnableAutoDepthStencil = TRUE; // 自動深度模板緩衝區
    presentParams.AutoDepthStencilFormat = D3DFMT_D24S8; // 深度模板格式
    presentParams.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE; // 立即呈現

    /*int totalVram = caps.TotalVideoMemory / 1024 / 1024;
    printf("TotalVideoMemory: %d MB\n", totalVram);*/

    IDirect3DDevice9* pDevice = NULL;
    if (FAILED(pD3D->CreateDevice(D3DADAPTER_DEFAULT, deviceType, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &presentParams, &pDevice)))
    {
        // 錯誤處理
        printf("Failed to get pDevice.\n");
        return -1;
    }

    pD3D->Release();

    return 0;
}
