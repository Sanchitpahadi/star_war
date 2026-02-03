#pragma once
class VertexBuffer
{
private:
	unsigned int m_Renderer;
public:
	VertexBuffer(float size, const void* data);
	~VertexBuffer();
	void Bind()const;
	void unBind()const;

};
