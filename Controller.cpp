#include "Controller.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"



Controller::Controller(GameObject * parent) :GameObject(parent, "Controller")
{

    transform_.position_.x = 7.0f;
    transform_.position_.z = 7.0f;

    transform_.rotate_.x = 45.0f;

}



Controller::~Controller()
{

}



void Controller::Initialize()
{
}



void Controller::Update()
{
    //右回転
    if (Input::IsKey(DIK_RIGHT))
    {
        transform_.rotate_.y += 1.0f;
    }

    //左回転
    if (Input::IsKey(DIK_LEFT))
    {
        transform_.rotate_.y -= 1.0f;
    }
    //transform_.rotate_.yの値に合わせてＹ軸回転させる行列
    XMMATRIX mRotateY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));

    //上回転
    if (Input::IsKey(DIK_UP))
    {
        transform_.rotate_.x += 1.0f;
        if (transform_.rotate_.x > 89)
        {
            transform_.rotate_.x = 89;
        }
       
    }

    //下回転
    if (Input::IsKey(DIK_DOWN))
    {
        transform_.rotate_.x -= 1.0f;
        if (transform_.rotate_.x < 0)
        {
            transform_.rotate_.x = 0;
        }
    
    }

    //transform_.rotate_.xの値に合わせてＸ軸回転させる行列
    XMMATRIX mRotateX = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));

   
    //現在地をベクトル型に変換
    XMVECTOR vPos = XMLoadFloat3(&transform_.position_);
   
    //前後移動
    XMVECTOR frontMove = XMVectorSet(0, 0, 0.1f, 0);             //奥向きのXMVECTOR構造体を用意し
    frontMove = XMVector3TransformCoord(frontMove, mRotateY);    //移動ベクトル回転
    if (Input::IsKey(DIK_W))
    {
        //移動
        vPos += frontMove;
    }
    if (Input::IsKey(DIK_S))
    {
        //移動
        vPos -= frontMove;
    }


    //左右移動
    XMVECTOR rightMove = XMVectorSet(0.1f, 0, 0, 0);             //右向きのXMVECTOR構造体を用意し
    rightMove = XMVector3TransformCoord(rightMove, mRotateY);    //移動ベクトル回転
    if (Input::IsKey(DIK_D))
    {
        //移動
        vPos += rightMove;
    }
    if (Input::IsKey(DIK_A))
    {
        //移動
        vPos -= rightMove;
    }
    XMStoreFloat3(&transform_.position_, vPos);

   
 
    //カメラ
    XMVECTOR vCam = XMVectorSet(0, 0, -10, 0);  //自撮り棒用意
    vCam = XMVector3TransformCoord(vCam, mRotateX * mRotateY);//自撮り棒回転
    Camera::SetPosition(vPos + vCam);
    Camera::SetTarget(transform_.position_); //カメラの見る位置はこのオブジェクトの位置

}



void Controller::Draw()
{

}



void Controller::Release()
{

}
