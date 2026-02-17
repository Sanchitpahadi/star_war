#pragma once
class VertexBuffer
{
private:
	unsigned int m_Renderer;
public:
	VertexBuffer();
	~VertexBuffer();
	void Init(float size,const void* data);

	void Bind()const;
	void unBind()const;

};
