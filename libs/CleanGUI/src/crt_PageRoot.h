// by Marius Versteegen, 2024

#pragma once
#include <assert.h>
#include <crt_FreeRTOS.h>
#include "crt_typesAndConstants.h"
#include "crt_Widget.h"
#include "crt_IDisplay.h"
#include "crt_ILogger.h"
namespace crt
{
	extern ILogger& logger;
	template <size_t MaxNofChildren> 
	class PageRoot : public Widget<MaxNofChildren>
	{
		
	public:
		using WBase = Widget<MaxNofChildren>;

		PageRoot(const char* strName, IDisplay& display)
			: WBase(strName, Vec2(0,0), CoordType::Pixels,
			Vec2(0,0), CoordType::Pixels, Alignment::TopLeft)
		{
			// init size with the size of the full screen:
			WBase::setDisplay(display);
			Vec2 size = display.getScreenSize();
			logger.logText("display.getScreenSize()=");
			logger.logInt32(size.x);
			logger.logInt32(size.y);
			WBase::setSize(WBase::getDisplay()->getScreenSize(), CoordType::Pixels);
		}

		/* override */ WidgetType getWidgetType()
		{
			return WidgetType::PageRoot;
		}
	};
};
