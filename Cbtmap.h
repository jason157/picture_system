#ifndef BTMAP_H
#define BTMAP_H

class Cbtmap : public CBitmap
{
public:
    DECLARE_DYNAMIC(Cbtmap)

// Constructors
    Cbtmap();

    void LoadBitmapEx(UINT nID, BOOL bIconBkgrd );
    CPalette *GetPalette(){return m_pPalette;};

// Implementation
public:
    virtual ~Cbtmap();

// Attributes
    int    m_Width;
    int m_Height;
// Operations

private:
    CPalette *m_pPalette;
};
#endif
