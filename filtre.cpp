//
// Created by khadimou on 20/01/2020.
//
#include "filtre.h"

filtre::filtre(int w, int h, byte *px) {
    m_w = w;
    m_h = h;
    m_px = px;
}

void filtre::rgbtogray() {
    byte gray;
    for(auto i=0;i<m_w*m_h*3;i++){
        gray = m_px[i+2];

        m_px[i] = gray;
        m_px[i+1] = gray;
        m_px[i+2] = gray;
    }
}




