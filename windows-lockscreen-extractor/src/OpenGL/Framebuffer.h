#pragma once

#include <vector>
#include <stdint.h>

class Framebuffer
{
public:
	Framebuffer() = default;
	Framebuffer(int32_t width, int32_t height);
	~Framebuffer();

	void Refresh();

	void Bind();
	void Unbind();

	void Resize(int32_t width, uint32_t height);
private:
	std::vector<uint32_t> m_ColorAttachments;
	uint32_t m_DepthAttachment;
	uint32_t m_FramebufferID;
	uint32_t m_Width, m_Height;
};
