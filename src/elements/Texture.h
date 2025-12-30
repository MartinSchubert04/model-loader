#pragma once

#include "common.h"
#include "renderer/Render.h"

class Texture {
private:
  std::string mFilepath;
  unsigned char *mLocalBuff;
  unsigned int mID;
  std::string mType;
  int mWidth, mHeight, mBPP;

public:
  Texture(std::string path);
  ~Texture();

  void bind(unsigned int slot = 0) const;
  void unbind() const;
  void destroy();

  inline int getWidth() const { return mWidth; };
  inline int getHeight() const { return mHeight; };
  inline std::string getType() const { return mType; };
  inline std::string getPath() const { return mFilepath; };
  inline int getID() const { return mID; };

  inline void setType(std::string type) { mType = type; };
};
