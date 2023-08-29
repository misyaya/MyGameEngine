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
    //‰E‰ñ“]
    if (Input::IsKey(DIK_RIGHT))
    {
        transform_.rotate_.y += 1.0f;
    }

    //¶‰ñ“]
    if (Input::IsKey(DIK_LEFT))
    {
        transform_.rotate_.y -= 1.0f;
    }
    //transform_.rotate_.y‚Ì’l‚É‡‚í‚¹‚Ä‚xŽ²‰ñ“]‚³‚¹‚és—ñ
    XMMATRIX mRotateY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));

    //ã‰ñ“]
    if (Input::IsKey(DIK_UP))
    {
        transform_.rotate_.x += 1.0f;
        if (transform_.rotate_.x > 89)
        {
            transform_.rotate_.x = 89;
        }
       
    }

    //‰º‰ñ“]
    if (Input::IsKey(DIK_DOWN))
    {
        transform_.rotate_.x -= 1.0f;
        if (transform_.rotate_.x < 0)
        {
            transform_.rotate_.x = 0;
        }
    
    }

    //transform_.rotate_.x‚Ì’l‚É‡‚í‚¹‚Ä‚wŽ²‰ñ“]‚³‚¹‚és—ñ
    XMMATRIX mRotateX = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));

   
    //Œ»Ý’n‚ðƒxƒNƒgƒ‹Œ^‚É•ÏŠ·
    XMVECTOR vPos = XMLoadFloat3(&transform_.position_);
   
    //‘OŒãˆÚ“®
    XMVECTOR frontMove = XMVectorSet(0, 0, 0.1f, 0);             //‰œŒü‚«‚ÌXMVECTOR\‘¢‘Ì‚ð—pˆÓ‚µ
    frontMove = XMVector3TransformCoord(frontMove, mRotateY);    //ˆÚ“®ƒxƒNƒgƒ‹‰ñ“]
    if (Input::IsKey(DIK_W))
    {
        //ˆÚ“®
        vPos += frontMove;
    }
    if (Input::IsKey(DIK_S))
    {
        //ˆÚ“®
        vPos -= frontMove;
    }


    //¶‰EˆÚ“®
    XMVECTOR rightMove = XMVectorSet(0.1f, 0, 0, 0);             //‰EŒü‚«‚ÌXMVECTOR\‘¢‘Ì‚ð—pˆÓ‚µ
    rightMove = XMVector3TransformCoord(rightMove, mRotateY);    //ˆÚ“®ƒxƒNƒgƒ‹‰ñ“]
    if (Input::IsKey(DIK_D))
    {
        //ˆÚ“®
        vPos += rightMove;
    }
    if (Input::IsKey(DIK_A))
    {
        //ˆÚ“®
        vPos -= rightMove;
    }
    XMStoreFloat3(&transform_.position_, vPos);

   
 
    //ƒJƒƒ‰
    XMVECTOR vCam = XMVectorSet(0, 0, -10, 0);  //Ž©ŽB‚è–_—pˆÓ
    vCam = XMVector3TransformCoord(vCam, mRotateX * mRotateY);//Ž©ŽB‚è–_‰ñ“]
    Camera::SetPosition(vPos + vCam);
    Camera::SetTarget(transform_.position_); //ƒJƒƒ‰‚ÌŒ©‚éˆÊ’u‚Í‚±‚ÌƒIƒuƒWƒFƒNƒg‚ÌˆÊ’u

}



void Controller::Draw()
{

}



void Controller::Release()
{

}
