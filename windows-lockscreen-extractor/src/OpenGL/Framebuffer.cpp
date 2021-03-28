#include "Framebuffer.h"

#include <glad/glad.h>
#include <iostream>

Framebuffer::Framebuffer(int32_t width, int32_t height)
	: m_Width(width), m_Height(height), m_FramebufferID(0), m_DepthAttachment(0)
{
	Refresh();
}

Framebuffer::~Framebuffer()
{
	glDeleteFramebuffers(1, &m_FramebufferID);
	glDeleteTextures(m_ColorAttachments.size(), m_ColorAttachments.data());
	glDeleteRenderbuffers(1, &m_DepthAttachment);
}

void Framebuffer::Refresh()
{
	if (m_FramebufferID)
	{
		glDeleteFramebuffers(1, &m_FramebufferID);
		glDeleteTextures(m_ColorAttachments.size(), m_ColorAttachments.data());
		glDeleteRenderbuffers(1, &m_DepthAttachment);

		m_ColorAttachments.clear();
	}

	glCreateFramebuffers(1, &m_FramebufferID);
	glBindFramebuffer(GL_FRAMEBUFFER, m_FramebufferID);

	// Create and attach textures
	// For now it is only one texture
	m_ColorAttachments.resize(1);
	glCreateTextures(GL_TEXTURE_2D, m_ColorAttachments.size(), m_ColorAttachments.data());

	for (size_t i = 0; i < m_ColorAttachments.size(); i++)
	{
		glBindTexture(GL_TEXTURE_2D, m_ColorAttachments[i]);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glBindTexture(GL_TEXTURE_2D, 0);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, m_ColorAttachments[i], 0);
	}

	// Create depth attachment as a renderbuffer object
	glCreateRenderbuffers(1, &m_DepthAttachment);
	glBindRenderbuffer(GL_RENDERBUFFER, m_DepthAttachment);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_Width, m_Height);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_DepthAttachment);

	if (m_ColorAttachments.size() > 0)
	{
		// TODO: replace it with assert
		if (m_ColorAttachments.size() > 4)
		{
			std::cout << "Only 4 color attachments are supported at most" << std::endl;
			return;
		}
		GLenum buffers[4] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
		glDrawBuffers(m_ColorAttachments.size(), buffers);
	}
	/*else if (m_ColorAttachments.empty())
	{
		glDrawBuffer(GL_NONE);
	}*/

	// TODO: replace it with assert
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cout << "Framebuffer is not complete" << std::endl;
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::Bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_FramebufferID);
	glViewport(0, 0, m_Width, m_Height);
}

void Framebuffer::Unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::Resize(int32_t width, uint32_t height)
{
	m_Width = width;
	m_Height = height;
	Refresh();
}
