/*
 * Copyright (C) 2008 Nokia Corporation
 * Author: Tomi Valkeinen <tomi.valkeinen@nokia.com>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published by
 * the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __OMAP_OMAPDSS_H
#define __OMAP_OMAPDSS_H

#include <linux/list.h>
#include <linux/kobject.h>
#include <linux/device.h>
#include <linux/fb.h>

#define DISPC_IRQ_FRAMEDONE		(1 << 0)
#define DISPC_IRQ_VSYNC			(1 << 1)
#define DISPC_IRQ_EVSYNC_EVEN		(1 << 2)
#define DISPC_IRQ_EVSYNC_ODD		(1 << 3)
#define DISPC_IRQ_ACBIAS_COUNT_STAT	(1 << 4)
#define DISPC_IRQ_PROG_LINE_NUM		(1 << 5)
#define DISPC_IRQ_GFX_FIFO_UNDERFLOW	(1 << 6)
#define DISPC_IRQ_GFX_END_WIN		(1 << 7)
#define DISPC_IRQ_PAL_GAMMA_MASK	(1 << 8)
#define DISPC_IRQ_OCP_ERR		(1 << 9)
#define DISPC_IRQ_VID1_FIFO_UNDERFLOW	(1 << 10)
#define DISPC_IRQ_VID1_END_WIN		(1 << 11)
#define DISPC_IRQ_VID2_FIFO_UNDERFLOW	(1 << 12)
#define DISPC_IRQ_VID2_END_WIN		(1 << 13)
#define DISPC_IRQ_SYNC_LOST		(1 << 14)
#define DISPC_IRQ_SYNC_LOST_DIGIT	(1 << 15)
#define DISPC_IRQ_WAKEUP		(1 << 16)
#define DISPC_IRQ_SYNC_LOST2		(1 << 17)
#define DISPC_IRQ_VSYNC2		(1 << 18)
#define DISPC_IRQ_VID3_END_WIN		(1 << 19)
#define DISPC_IRQ_VID3_FIFO_UNDERFLOW	(1 << 20)
#define DISPC_IRQ_ACBIAS_COUNT_STAT2	(1 << 21)
#define DISPC_IRQ_FRAMEDONE2		(1 << 22)
#define DISPC_IRQ_FRAMEDONETV		(1 << 24)

struct omap_dss_device;
struct omap_overlay_manager;

enum omap_display_type {
	OMAP_DISPLAY_TYPE_NONE		= 0,
	OMAP_DISPLAY_TYPE_DPI		= 1 << 0,
	OMAP_DISPLAY_TYPE_DBI		= 1 << 1,
	OMAP_DISPLAY_TYPE_SDI		= 1 << 2,
	OMAP_DISPLAY_TYPE_DSI		= 1 << 3,
	OMAP_DISPLAY_TYPE_VENC		= 1 << 4,
	OMAP_DISPLAY_TYPE_HDMI		= 1 << 5,
};

enum omap_dsi_te_type {
	OMAP_DSI_TE_MIPI_PHY	= 0,
	OMAP_DSI_TE_CMOS_TE_0	= 1
};

/* Denotes the manual power control state of a display */
enum omap_dss_manual_pwrctrl {
	OMAP_DSS_MPC_DISABLED = 0,
	OMAP_DSS_MPC_SUSPEND,
	OMAP_DSS_MPC_RESUME,
};

enum omap_plane {
	OMAP_DSS_GFX	= 0,
	OMAP_DSS_VIDEO1	= 1,
	OMAP_DSS_VIDEO2	= 2,
	OMAP_DSS_VIDEO3 = 3,
};

enum omap_channel {
	OMAP_DSS_CHANNEL_LCD	= 0,
	OMAP_DSS_CHANNEL_DIGIT	= 1,
	OMAP_DSS_CHANNEL_LCD2	= 2,
};

enum omap_color_mode {
	OMAP_DSS_COLOR_CLUT1	= 1 << 0,  /* BITMAP 1 */
	OMAP_DSS_COLOR_CLUT2	= 1 << 1,  /* BITMAP 2 */
	OMAP_DSS_COLOR_CLUT4	= 1 << 2,  /* BITMAP 4 */
	OMAP_DSS_COLOR_CLUT8	= 1 << 3,  /* BITMAP 8 */
	OMAP_DSS_COLOR_RGB12U	= 1 << 4,  /* RGB12, 16-bit container */
	OMAP_DSS_COLOR_ARGB16	= 1 << 5,  /* ARGB16 */
	OMAP_DSS_COLOR_RGB16	= 1 << 6,  /* RGB16 */
	OMAP_DSS_COLOR_RGB24U	= 1 << 7,  /* RGB24, 32-bit container */
	OMAP_DSS_COLOR_RGB24P	= 1 << 8,  /* RGB24, 24-bit container */
	OMAP_DSS_COLOR_YUV2	= 1 << 9,  /* YUV2 4:2:2 co-sited */
	OMAP_DSS_COLOR_UYVY	= 1 << 10, /* UYVY 4:2:2 co-sited */
	OMAP_DSS_COLOR_ARGB32	= 1 << 11, /* ARGB32 */
	OMAP_DSS_COLOR_RGBA32	= 1 << 12, /* RGBA32 */
	OMAP_DSS_COLOR_RGBX32	= 1 << 13, /* RGBx32 */
	OMAP_DSS_COLOR_NV12		= 1 << 14, /* NV12 format: YUV 4:2:0 */
	OMAP_DSS_COLOR_RGBA16		= 1 << 15, /* RGBA16 - 4444 */
	OMAP_DSS_COLOR_RGBX16		= 1 << 16, /* RGBx16 - 4444 */
	OMAP_DSS_COLOR_ARGB16_1555	= 1 << 17, /* ARGB16 - 1555 */
	OMAP_DSS_COLOR_XRGB16_1555	= 1 << 18, /* xRGB16 - 1555 */
};

/* Writeback data structures */
enum omap_writeback_source {
	OMAP_WB_LCD1		= 0,
	OMAP_WB_TV		= 1,
	OMAP_WB_LCD2		= 2,
	OMAP_WB_GFX		= 3,
	OMAP_WB_VID1		= 4,
	OMAP_WB_VID2		= 5,
	OMAP_WB_VID3		= 6
};

enum omap_writeback_mode {
	OMAP_WB_CAPTURE_MODE	= 0x0,
	OMAP_WB_MEM2MEM_MODE	= 0x1,
};

enum omap_lcd_display_type {
	OMAP_DSS_LCD_DISPLAY_STN,
	OMAP_DSS_LCD_DISPLAY_TFT,
};

enum omap_dss_load_mode {
	OMAP_DSS_LOAD_CLUT_AND_FRAME	= 0,
	OMAP_DSS_LOAD_CLUT_ONLY		= 1,
	OMAP_DSS_LOAD_FRAME_ONLY	= 2,
	OMAP_DSS_LOAD_CLUT_ONCE_FRAME	= 3,
};

enum omap_dss_trans_key_type {
	OMAP_DSS_COLOR_KEY_GFX_DST = 0,
	OMAP_DSS_COLOR_KEY_VID_SRC = 1,
};

enum omap_rfbi_te_mode {
	OMAP_DSS_RFBI_TE_MODE_1 = 1,
	OMAP_DSS_RFBI_TE_MODE_2 = 2,
};

enum omap_panel_config {
	OMAP_DSS_LCD_IVS		= 1<<0,
	OMAP_DSS_LCD_IHS		= 1<<1,
	OMAP_DSS_LCD_IPC		= 1<<2,
	OMAP_DSS_LCD_IEO		= 1<<3,
	OMAP_DSS_LCD_RF			= 1<<4,
	OMAP_DSS_LCD_ONOFF		= 1<<5,

	OMAP_DSS_LCD_TFT		= 1<<20,
};

enum omap_dss_dsi_type {
	OMAP_DSS_DSI_TYPE_CMD_MODE = 0,
	OMAP_DSS_DSI_TYPE_VIDEO_MODE,
};

enum omap_dss_venc_type {
	OMAP_DSS_VENC_TYPE_COMPOSITE,
	OMAP_DSS_VENC_TYPE_SVIDEO,
};

enum omap_display_caps {
	OMAP_DSS_DISPLAY_CAP_MANUAL_UPDATE	= 1 << 0,
	OMAP_DSS_DISPLAY_CAP_TEAR_ELIM		= 1 << 1,
};

enum omap_dss_update_mode {
	OMAP_DSS_UPDATE_DISABLED = 0,
	OMAP_DSS_UPDATE_AUTO,
	OMAP_DSS_UPDATE_MANUAL,
};

enum omap_dss_display_state {
	OMAP_DSS_DISPLAY_DISABLED = 0,
	OMAP_DSS_DISPLAY_ACTIVE,
	OMAP_DSS_DISPLAY_SUSPENDED,
	OMAP_DSS_DISPLAY_TRANSITION,
};

enum omap_dispc_irq_type {
	OMAP_DISPC_IRQ_TYPE_FRAMEDONE,
	OMAP_DISPC_IRQ_TYPE_VSYNC,
};

/* XXX perhaps this should be removed */
enum omap_dss_overlay_managers {
	OMAP_DSS_OVL_MGR_LCD,
	OMAP_DSS_OVL_MGR_TV,
	OMAP_DSS_OVL_MGR_LCD2,
};

enum omap_dss_rotation_type {
	OMAP_DSS_ROT_DMA = 0,
	OMAP_DSS_ROT_VRFB = 1,
	OMAP_DSS_ROT_TILER = 2,
};

/* clockwise rotation angle */
enum omap_dss_rotation_angle {
	OMAP_DSS_ROT_0   = 0,
	OMAP_DSS_ROT_90  = 1,
	OMAP_DSS_ROT_180 = 2,
	OMAP_DSS_ROT_270 = 3,
};

enum omap_overlay_caps {
	OMAP_DSS_OVL_CAP_SCALE = 1 << 0,
	OMAP_DSS_OVL_CAP_DISPC = 1 << 1,
};

enum omap_overlay_manager_caps {
	OMAP_DSS_OVL_MGR_CAP_DISPC = 1 << 0,
};

enum omap_dss_clk_source {
	OMAP_DSS_CLK_SRC_FCK = 0,		/* OMAP2/3: DSS1_ALWON_FCLK
						 * OMAP4: DSS_FCLK */
	OMAP_DSS_CLK_SRC_DSI_PLL_HSDIV_DISPC,	/* OMAP3: DSI1_PLL_FCLK
						 * OMAP4: PLL1_CLK1 */
	OMAP_DSS_CLK_SRC_DSI_PLL_HSDIV_DSI,	/* OMAP3: DSI2_PLL_FCLK
						 * OMAP4: PLL1_CLK2 */
	OMAP_DSS_CLK_SRC_DSI2_PLL_HSDIV_DISPC,	/* OMAP4: PLL2_CLK1 */
	OMAP_DSS_CLK_SRC_DSI2_PLL_HSDIV_DSI,	/* OMAP4: PLL2_CLK2 */
};

enum omap_overlay_zorder {
	OMAP_DSS_OVL_ZORDER_0   = 0,
	OMAP_DSS_OVL_ZORDER_1   = 1,
	OMAP_DSS_OVL_ZORDER_2   = 2,
	OMAP_DSS_OVL_ZORDER_3   = 3,
};

/* RFBI */

struct rfbi_timings {
	int cs_on_time;
	int cs_off_time;
	int we_on_time;
	int we_off_time;
	int re_on_time;
	int re_off_time;
	int we_cycle_time;
	int re_cycle_time;
	int cs_pulse_width;
	int access_time;

	int clk_div;

	u32 tim[5];             /* set by rfbi_convert_timings() */

	int converted;
};

void omap_rfbi_write_command(const void *buf, u32 len);
void omap_rfbi_read_data(void *buf, u32 len);
void omap_rfbi_write_data(const void *buf, u32 len);
void omap_rfbi_write_pixels(const void __iomem *buf, int scr_width,
		u16 x, u16 y,
		u16 w, u16 h);
int omap_rfbi_enable_te(bool enable, unsigned line);
int omap_rfbi_setup_te(enum omap_rfbi_te_mode mode,
			     unsigned hs_pulse_time, unsigned vs_pulse_time,
			     int hs_pol_inv, int vs_pol_inv, int extif_div);
void rfbi_bus_lock(void);
void rfbi_bus_unlock(void);

/* DSI */
void dsi_bus_lock(struct omap_dss_device *dssdev);
void dsi_bus_unlock(struct omap_dss_device *dssdev);
int dsi_vc_dcs_write(struct omap_dss_device *dssdev, int channel, u8 *data,
		int len);
int dsi_vc_dcs_write_0(struct omap_dss_device *dssdev, int channel,
		u8 dcs_cmd);
int dsi_vc_dcs_write_1(struct omap_dss_device *dssdev, int channel, u8 dcs_cmd,
		u8 param);
int dsi_vc_dcs_write_nosync(struct omap_dss_device *dssdev, int channel,
		u8 *data, int len);
int dsi_vc_dcs_read(struct omap_dss_device *dssdev, int channel, u8 dcs_cmd,
		u8 *buf, int buflen);
int dsi_vc_dcs_read_1(struct omap_dss_device *dssdev, int channel, u8 dcs_cmd,
		u8 *data);
int dsi_vc_dcs_read_2(struct omap_dss_device *dssdev, int channel, u8 dcs_cmd,
		u8 *data1, u8 *data2);
int dsi_vc_gen_write_nosync(struct omap_dss_device *dssdev, int channel,
		u8 *data, int len);
int dsi_vc_gen_write(struct omap_dss_device *dssdev, int channel,
		u8 *data, int len);
int dsi_vc_set_max_rx_packet_size(struct omap_dss_device *dssdev, int channel,
		u16 len);
int dsi_vc_send_null(struct omap_dss_device *dssdev, int channel);
int dsi_vc_send_bta_sync(struct omap_dss_device *dssdev, int channel);

int dsi_video_mode_enable(struct omap_dss_device *dssdev, u8 data_type);
void dsi_video_mode_disable(struct omap_dss_device *dssdev);

int dsi_vc_gen_read_2(struct omap_dss_device *dssdev, int channel, u16 cmd,
		u8 *buf, int buflen);
void dsi_videomode_panel_preinit(struct omap_dss_device *dssdev);


/* Board specific data */
struct omap_dss_board_info {
	int (*get_context_loss_count)(struct device *dev);
	int num_devices;
	struct omap_dss_device **devices;
	struct omap_dss_device *default_device;
	void (*dsi_mux_pads)(bool enable);
};

#if defined(CONFIG_OMAP2_DSS_MODULE) || defined(CONFIG_OMAP2_DSS)
/* Init with the board info */
extern int omap_display_init(struct omap_dss_board_info *board_data);
#else
static inline int omap_display_init(struct omap_dss_board_info *board_data)
{
	return 0;
}
#endif

struct omap_display_platform_data {
	struct omap_dss_board_info *board_data;
	/* TODO: Additional members to be added when PM is considered */
};

struct omap_video_timings {
	/* Unit: pixels */
	u16 x_res;
	/* Unit: pixels */
	u16 y_res;
	/* Unit: KHz */
	u32 pixel_clock;
	/* Unit: pixel clocks */
	u16 hsw;	/* Horizontal synchronization pulse width */
	/* Unit: pixel clocks */
	u16 hfp;	/* Horizontal front porch */
	/* Unit: pixel clocks */
	u16 hbp;	/* Horizontal back porch */
	/* Unit: line clocks */
	u16 vsw;	/* Vertical synchronization pulse width */
	/* Unit: line clocks */
	u16 vfp;	/* Vertical front porch */
	/* Unit: line clocks */
	u16 vbp;	/* Vertical back porch */
};

struct omap_dsi_video_timings {
	/* Unit: pixel clocks */
	u16 hsa;        /* Horizontal synch active */
	/* Unit: pixel clocks */
	u16 hfp;        /* Horizontal front porch */
	/* Unit: pixel clocks */
	u16 hbp;        /* Horizontal back porch */
	/* Unit: line clocks */
	u16 vsa;        /* Vertical synch active */
	/* Unit: line clocks */
	u16 vfp;        /* Vertical front porch */
	/* Unit: line clocks */
	u16 vbp;        /* Vertical back porch */
};

struct omap_dsi_hs_mode_timing {
	/* time in nsec */
	u32 ths_prepare;
	u32 ths_prepare_ths_zero;
	u32 ths_trail;
	u32 ths_exit;
	u32 tlpx_half;
	u32 tclk_trail;
	u32 tclk_prepare;
	u32 tclk_zero;
};

#ifdef CONFIG_OMAP2_DSS_VENC
/* Hardcoded timings for tv modes. Venc only uses these to
 * identify the mode, and does not actually use the configs
 * itself. However, the configs should be something that
 * a normal monitor can also show */
extern const struct omap_video_timings omap_dss_pal_timings;
extern const struct omap_video_timings omap_dss_ntsc_timings;
#endif

enum omapdss_completion_status {
	DSS_COMPLETION_PROGRAMMED	= (1 << 1),
	DSS_COMPLETION_DISPLAYED	= (1 << 2),

	DSS_COMPLETION_CHANGED_SET	= (1 << 3),
	DSS_COMPLETION_CHANGED_CACHE	= (1 << 4),
	DSS_COMPLETION_CHANGED		= (3 << 3),

	DSS_COMPLETION_RELEASED		= (15 << 5),
	DSS_COMPLETION_ECLIPSED_SET	= (1 << 5),
	DSS_COMPLETION_ECLIPSED_CACHE	= (1 << 6),
	DSS_COMPLETION_ECLIPSED_SHADOW	= (1 << 7),
	DSS_COMPLETION_TORN		= (1 << 8),
};

struct omapdss_ovl_cb {
	/* optional callback method */
	u32 (*fn)(void *data, int id, int status);
	void *data;
	u32 mask;
};

struct omap_dss_cpr_coefs {
	s16 rr, rg, rb;
	s16 gr, gg, gb;
	s16 br, bg, bb;
};

struct omap_dss_cconv_coefs {
	s16 ry, rcr, rcb;
	s16 gy, gcr, gcb;
	s16 by, bcr, bcb;
	u16 full_range;
} __attribute__ ((aligned(4)));

struct omap_overlay_info {
	bool enabled;

	u32 paddr;
	void __iomem *vaddr;
	u32 p_uv_addr;  /* for NV12 format */
	u16 screen_width;
	u16 width;
	u16 height;
	enum omap_color_mode color_mode;
	u8 rotation;
	enum omap_dss_rotation_type rotation_type;
	bool mirror;

	u16 pos_x;
	u16 pos_y;
	u16 out_width;	/* if 0, out_width == width */
	u16 out_height;	/* if 0, out_height == height */
	u8 global_alpha;
	u8 pre_mult_alpha;
	enum omap_overlay_zorder zorder;
	u16 min_x_decim, max_x_decim, min_y_decim, max_y_decim;
	struct omap_dss_cconv_coefs cconv;

	struct omapdss_ovl_cb cb;
};

struct omap_overlay {
	struct kobject kobj;
	struct list_head list;

	/* static fields */
	const char *name;
	int id;
	enum omap_color_mode supported_modes;
	enum omap_overlay_caps caps;

	/* dynamic fields */
	struct omap_overlay_manager *manager;
	struct omap_overlay_info info;

	/* if true, info has been changed, but not applied() yet */
	bool info_dirty;

	int (*set_manager)(struct omap_overlay *ovl,
		struct omap_overlay_manager *mgr);
	int (*unset_manager)(struct omap_overlay *ovl);

	int (*set_overlay_info)(struct omap_overlay *ovl,
			struct omap_overlay_info *info);
	void (*get_overlay_info)(struct omap_overlay *ovl,
			struct omap_overlay_info *info);

	int (*wait_for_go)(struct omap_overlay *ovl);
};

struct omap_overlay_manager_info {
	u32 default_color;

	enum omap_dss_trans_key_type trans_key_type;
	u32 trans_key;
	bool trans_enabled;

	bool alpha_enabled;

	struct omapdss_ovl_cb cb;

	bool cpr_enable;
	struct omap_dss_cpr_coefs cpr_coefs;
};

struct omap_overlay_manager {
	struct kobject kobj;
	struct list_head list;

	/* static fields */
	const char *name;
	int id;
	enum omap_overlay_manager_caps caps;
	int num_overlays;
	struct omap_overlay **overlays;
	enum omap_display_type supported_displays;

	/* dynamic fields */
	struct omap_dss_device *device;
	struct omap_overlay_manager_info info;

	bool device_changed;
	/* if true, info has been changed but not applied() yet */
	bool info_dirty;

	int (*set_device)(struct omap_overlay_manager *mgr,
		struct omap_dss_device *dssdev);
	int (*unset_device)(struct omap_overlay_manager *mgr);

	int (*set_manager_info)(struct omap_overlay_manager *mgr,
			struct omap_overlay_manager_info *info);
	void (*get_manager_info)(struct omap_overlay_manager *mgr,
			struct omap_overlay_manager_info *info);

	int (*apply)(struct omap_overlay_manager *mgr);
	int (*wait_for_go)(struct omap_overlay_manager *mgr);
	int (*wait_for_vsync)(struct omap_overlay_manager *mgr);
	int (*blank)(struct omap_overlay_manager *mgr, bool wait_for_vsync);
	void (*dump_cb)(struct omap_overlay_manager *mgr, struct seq_file *s);

	int (*enable)(struct omap_overlay_manager *mgr);
	int (*disable)(struct omap_overlay_manager *mgr);
};

struct omap_dss_device {
	struct device dev;

	enum omap_display_type type;

	enum omap_channel channel;

	bool first_vsync;
	bool sync_lost_error;

	union {
		struct {
			u8 data_lines;
		} dpi;

		struct {
			u8 channel;
			u8 data_lines;
		} rfbi;

		struct {
			u8 datapairs;
		} sdi;

		struct {
			enum omap_dss_dsi_type type;
			u8 clk_lane;
			u8 clk_pol;
			u8 data1_lane;
			u8 data1_pol;
			u8 data2_lane;
			u8 data2_pol;
			u8 data3_lane;
			u8 data3_pol;
			u8 data4_lane;
			u8 data4_pol;
			int module;

			bool ext_te;
			u8 ext_te_gpio;
			struct omap_dsi_video_timings vm_timing;
			struct omap_dsi_hs_mode_timing hs_timing;
			bool d2l_use_ulps;
		} dsi;

		struct {
			enum omap_dss_venc_type type;
			bool invert_polarity;
		} venc;
	} phy;

	struct {
		struct {
			struct {
				u16 lck_div;
				u16 pck_div;
				enum omap_dss_clk_source lcd_clk_src;
			} channel;

			enum omap_dss_clk_source dispc_fclk_src;
		} dispc;

		struct {
			u16 regn;
			u16 regm;
			u16 regm_dispc;
			u16 regm_dsi;

			u16 lp_clk_div;
			unsigned offset_ddr_clk;
			enum omap_dss_clk_source dsi_fclk_src;
		} dsi;

		struct {
			u16 regn;
			u16 regm2;

			u32 max_pixclk_khz;
		} hdmi;
	} clocks;

	struct {
		struct omap_video_timings timings;

		int acbi;	/* ac-bias pin transitions per interrupt */
		/* Unit: line clocks */
		int acb;	/* ac-bias pin frequency */

		enum omap_panel_config config;
		unsigned long panel_id;
		u32 width_in_mm;
		u32 height_in_mm;
		struct fb_monspecs monspecs;

		u32 width_in_um;
		u32 height_in_um;
	} panel;

	struct {
		u8 pixel_size;
		struct rfbi_timings rfbi_timings;
	} ctrl;

	int reset_gpio;
	int hpd_gpio;

	bool skip_init;
	int max_backlight_level;


	const char *name;

	/* used to match device to driver */
	const char *driver_name;

	void *data;

	struct omap_dss_driver *driver;

	enum omap_dss_manual_pwrctrl manual_power_control;
	int (*platform_enable_hpd)(struct omap_dss_device *dssdev);
	void (*platform_disable_hpd)(struct omap_dss_device *dssdev);

	/* helper variable for driver suspend/resume */
	bool activate_after_resume;

	enum omap_display_caps caps;

	struct omap_overlay_manager *manager;

	enum omap_dss_display_state state;

	struct blocking_notifier_head state_notifiers;

	/* HDMI specific */
	void (*enable_device_detect)(struct omap_dss_device *dssdev, u8 enable);
	bool (*get_device_detect)(struct omap_dss_device *dssdev);
	int (*get_device_connected)(struct omap_dss_device *dssdev);

	/* platform specific  */
	int (*platform_enable)(struct omap_dss_device *dssdev);
	void (*platform_disable)(struct omap_dss_device *dssdev);
	int (*set_backlight)(struct omap_dss_device *dssdev, int level);
	int (*get_backlight)(struct omap_dss_device *dssdev);
};

struct omap_dss_driver {
	struct device_driver driver;

	int (*probe)(struct omap_dss_device *);
	void (*remove)(struct omap_dss_device *);

	int (*enable)(struct omap_dss_device *display);
	int (*framedone)(struct omap_dss_device *display);

	void (*disable)(struct omap_dss_device *display);
	int (*suspend)(struct omap_dss_device *display);
	int (*resume)(struct omap_dss_device *display);
	int (*run_test)(struct omap_dss_device *display, int test);

	int (*set_update_mode)(struct omap_dss_device *dssdev,
			enum omap_dss_update_mode);
	enum omap_dss_update_mode (*get_update_mode)(
			struct omap_dss_device *dssdev);

	int (*update)(struct omap_dss_device *dssdev,
			       u16 x, u16 y, u16 w, u16 h);
	int (*sync)(struct omap_dss_device *dssdev);

	int (*enable_te)(struct omap_dss_device *dssdev, bool enable);
	int (*get_te)(struct omap_dss_device *dssdev);
	bool (*support_te)(struct omap_dss_device *dssdev);
	bool (*manual_te_trigger)(struct omap_dss_device *dssdev);

	u8 (*get_rotate)(struct omap_dss_device *dssdev);
	int (*set_rotate)(struct omap_dss_device *dssdev, u8 rotate);

	bool (*get_mirror)(struct omap_dss_device *dssdev);
	int (*set_mirror)(struct omap_dss_device *dssdev, bool enable);

	int (*memory_read)(struct omap_dss_device *dssdev,
			void *buf, size_t size,
			u16 x, u16 y, u16 w, u16 h);

	void (*get_resolution)(struct omap_dss_device *dssdev,
			u16 *xres, u16 *yres);
	void (*get_dimensions)(struct omap_dss_device *dssdev,
			u32 *width, u32 *height);
	int (*get_recommended_bpp)(struct omap_dss_device *dssdev);

	int (*check_timings)(struct omap_dss_device *dssdev,
			struct omap_video_timings *timings);
	void (*set_timings)(struct omap_dss_device *dssdev,
			struct omap_video_timings *timings);
	void (*get_timings)(struct omap_dss_device *dssdev,
			struct omap_video_timings *timings);

	int (*set_wss)(struct omap_dss_device *dssdev, u32 wss);
	u32 (*get_wss)(struct omap_dss_device *dssdev);
	int (*get_modedb)(struct omap_dss_device *dssdev,
			  struct fb_videomode *modedb,
			  int modedb_len);

	void (*enable_device_detect)(struct omap_dss_device *dssdev, u8 enable);
	bool (*get_device_detect)(struct omap_dss_device *dssdev);
	int (*get_device_connected)(struct omap_dss_device *dssdev);


	int (*set_mode)(struct omap_dss_device *dssdev,
			struct fb_videomode *mode);

	int (*reg_read)(struct omap_dss_device *dssdev, u8 address, u16 size,
			u8 *buf, u8 use_hs_mode);
	int (*reg_write)(struct omap_dss_device *dssdev, u16 size, u8 *buf,
		u8 use_hs_mode);

	int (*get_dsi_vc_chnls)(struct omap_dss_device *dssdev,
			u8 *dsi_vc_cmd_chnl, u8 *dsi_vc_video_chnl);

	/* for wrapping around state changes */
	void (*disable_orig)(struct omap_dss_device *display);
	int (*enable_orig)(struct omap_dss_device *display);
};

int omap_dss_register_driver(struct omap_dss_driver *);
void omap_dss_unregister_driver(struct omap_dss_driver *);

void omap_dss_get_device(struct omap_dss_device *dssdev);
void omap_dss_put_device(struct omap_dss_device *dssdev);
#define for_each_dss_dev(d) while ((d = omap_dss_get_next_device(d)) != NULL)
struct omap_dss_device *omap_dss_get_next_device(struct omap_dss_device *from);
struct omap_dss_device *omap_dss_find_device(void *data,
		int (*match)(struct omap_dss_device *dssdev, void *data));

int omap_dss_start_device(struct omap_dss_device *dssdev);
void omap_dss_stop_device(struct omap_dss_device *dssdev);

int omap_dss_get_num_overlay_managers(void);
struct omap_overlay_manager *omap_dss_get_overlay_manager(int num);

int omap_dss_get_num_overlays(void);
struct omap_overlay *omap_dss_get_overlay(int num);

void omapdss_default_get_resolution(struct omap_dss_device *dssdev,
		u16 *xres, u16 *yres);
int omapdss_default_get_recommended_bpp(struct omap_dss_device *dssdev);

typedef void (*omap_dispc_isr_t) (void *arg, u32 mask);
int omap_dispc_register_isr(omap_dispc_isr_t isr, void *arg, u32 mask);
int omap_dispc_unregister_isr(omap_dispc_isr_t isr, void *arg, u32 mask);

int omap_dispc_wait_for_irq_timeout(u32 irqmask, unsigned long timeout);
int omap_dispc_wait_for_irq_interruptible_timeout(u32 irqmask,
		unsigned long timeout);

void omap_dispc_set_irq_type(int channel, enum omap_dispc_irq_type type);

#define to_dss_driver(x) container_of((x), struct omap_dss_driver, driver)
#define to_dss_device(x) container_of((x), struct omap_dss_device, dev)

void omapdss_display_get_dimensions(struct omap_dss_device *dssdev,
				u32 *width_in_um, u32 *height_in_um);

void omapdss_dsi_vc_enable_hs(struct omap_dss_device *dssdev, int channel,
		bool enable);
int omapdss_dsi_enable_te(struct omap_dss_device *dssdev, bool enable);

int omap_dsi_prepare_update(struct omap_dss_device *dssdev,
				    u16 *x, u16 *y, u16 *w, u16 *h,
				    bool enlarge_update_area);
int omap_dsi_update(struct omap_dss_device *dssdev,
		int channel,
		u16 x, u16 y, u16 w, u16 h,
		void (*callback)(int, void *), void *data);
int omap_dsi_request_vc(struct omap_dss_device *dssdev, int *channel);
int omap_dsi_set_vc_id(struct omap_dss_device *dssdev, int channel, int vc_id);
void omap_dsi_release_vc(struct omap_dss_device *dssdev, int channel);

int omapdss_dsi_display_enable(struct omap_dss_device *dssdev);
void omapdss_dsi_display_disable(struct omap_dss_device *dssdev,
		bool disconnect_lanes, bool enter_ulps);

int omapdss_dpi_display_enable(struct omap_dss_device *dssdev);
void omapdss_dpi_display_disable(struct omap_dss_device *dssdev);
void dpi_set_timings(struct omap_dss_device *dssdev,
			struct omap_video_timings *timings);
int dpi_check_timings(struct omap_dss_device *dssdev,
			struct omap_video_timings *timings);

int omapdss_sdi_display_enable(struct omap_dss_device *dssdev);
void omapdss_sdi_display_disable(struct omap_dss_device *dssdev);

int omapdss_rfbi_display_enable(struct omap_dss_device *dssdev);
void omapdss_rfbi_display_disable(struct omap_dss_device *dssdev);
int omap_rfbi_prepare_update(struct omap_dss_device *dssdev,
		u16 *x, u16 *y, u16 *w, u16 *h);
int omap_rfbi_update(struct omap_dss_device *dssdev,
		u16 x, u16 y, u16 w, u16 h,
		void (*callback)(void *), void *data);
int omap_rfbi_configure(struct omap_dss_device *dssdev, int pixel_size,
		int data_lines);

int omap_dss_manager_unregister_callback(struct omap_overlay_manager *mgr,
					 struct omapdss_ovl_cb *cb);

/* generic callback handling */
static inline void dss_ovl_cb(struct omapdss_ovl_cb *cb, int id, int status)
{
	if (cb->fn && (cb->mask & status))
		cb->mask &= cb->fn(cb->data, id, status);
	if (status & DSS_COMPLETION_RELEASED)
		cb->mask = 0;
	if (!cb->mask)
		cb->fn = NULL;
}

#endif
