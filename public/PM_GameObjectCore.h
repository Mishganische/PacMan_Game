//
// Created by MIKHAIL ARZUMANOV on 2025. 03. 20..
//

#ifndef PM_GAMEOBJECT_H
#define PM_GAMEOBJECT_H

class PM_GameObjectCore {
public:
    PM_GameObjectCore(int startX, int startY): x(startX), y(startY) {};
    virtual ~PM_GameObjectCore() = default;

    virtual int Update()=0;
    virtual void Render() const =0;

    int GetX() const{return x;}
    int GetY() const{return y;}

    void SetX(int NewX){x = NewX;}
    void SetY(int NewY){y = NewY;}

protected:
    int x=2;
    int y=1;



};



#endif //PM_GAMEOBJECT_H
