#!/usr/bin/env python3
# -*- coding: utf-8 -*-

#
# SPDX-License-Identifier: GPL-3.0
#
# GNU Radio Python Flow Graph
# Title: AR02
# Author: pedro
# GNU Radio version: 3.8.1.0

from distutils.version import StrictVersion

if __name__ == '__main__':
    import ctypes
    import sys
    if sys.platform.startswith('linux'):
        try:
            x11 = ctypes.cdll.LoadLibrary('libX11.so')
            x11.XInitThreads()
        except:
            print("Warning: failed to XInitThreads()")

from PyQt5 import Qt
from gnuradio import qtgui
from gnuradio.filter import firdes
import sip
from gnuradio import analog
from gnuradio import blocks
from gnuradio import filter
from gnuradio import gr
import sys
import signal
from argparse import ArgumentParser
from gnuradio.eng_arg import eng_float, intx
from gnuradio import eng_notation
from gnuradio.qtgui import Range, RangeWidget
from gnuradio import qtgui

class m180108140_Exp06_AR02(gr.top_block, Qt.QWidget):

    def __init__(self):
        gr.top_block.__init__(self, "AR02")
        Qt.QWidget.__init__(self)
        self.setWindowTitle("AR02")
        qtgui.util.check_set_qss()
        try:
            self.setWindowIcon(Qt.QIcon.fromTheme('gnuradio-grc'))
        except:
            pass
        self.top_scroll_layout = Qt.QVBoxLayout()
        self.setLayout(self.top_scroll_layout)
        self.top_scroll = Qt.QScrollArea()
        self.top_scroll.setFrameStyle(Qt.QFrame.NoFrame)
        self.top_scroll_layout.addWidget(self.top_scroll)
        self.top_scroll.setWidgetResizable(True)
        self.top_widget = Qt.QWidget()
        self.top_scroll.setWidget(self.top_widget)
        self.top_layout = Qt.QVBoxLayout(self.top_widget)
        self.top_grid_layout = Qt.QGridLayout()
        self.top_layout.addLayout(self.top_grid_layout)

        self.settings = Qt.QSettings("GNU Radio", "m180108140_Exp06_AR02")

        try:
            if StrictVersion(Qt.qVersion()) < StrictVersion("5.0.0"):
                self.restoreGeometry(self.settings.value("geometry").toByteArray())
            else:
                self.restoreGeometry(self.settings.value("geometry"))
        except:
            pass

        ##################################################
        # Variables
        ##################################################
        self.samp_rate = samp_rate = 200000
        self.pi = pi = 3.14159265359
        self.G_ruido_FM = G_ruido_FM = 0
        self.G_ruido_AM = G_ruido_AM = 0
        self.G_demod_AM = G_demod_AM = 1
        self.Delay_FM = Delay_FM = 0
        self.Delay_AM = Delay_AM = 0
        self.A = A = 0.5

        ##################################################
        # Blocks
        ##################################################
        self._G_ruido_FM_range = Range(0, 10, 0.1, 0, 200)
        self._G_ruido_FM_win = RangeWidget(self._G_ruido_FM_range, self.set_G_ruido_FM, 'G_ruido_FM', "counter_slider", float)
        self.top_grid_layout.addWidget(self._G_ruido_FM_win, 3, 4, 1, 1)
        for r in range(3, 4):
            self.top_grid_layout.setRowStretch(r, 1)
        for c in range(4, 5):
            self.top_grid_layout.setColumnStretch(c, 1)
        self._G_ruido_AM_range = Range(0, 10, 0.1, 0, 200)
        self._G_ruido_AM_win = RangeWidget(self._G_ruido_AM_range, self.set_G_ruido_AM, 'G_ruido_AM', "counter_slider", float)
        self.top_grid_layout.addWidget(self._G_ruido_AM_win, 2, 4, 1, 1)
        for r in range(2, 3):
            self.top_grid_layout.setRowStretch(r, 1)
        for c in range(4, 5):
            self.top_grid_layout.setColumnStretch(c, 1)
        self._G_demod_AM_range = Range(0, 100, 1, 1, 200)
        self._G_demod_AM_win = RangeWidget(self._G_demod_AM_range, self.set_G_demod_AM, 'G_demod_AM', "counter_slider", float)
        self.top_grid_layout.addWidget(self._G_demod_AM_win, 4, 4, 1, 1)
        for r in range(4, 5):
            self.top_grid_layout.setRowStretch(r, 1)
        for c in range(4, 5):
            self.top_grid_layout.setColumnStretch(c, 1)
        self._Delay_FM_range = Range(0, 400, 1, 0, 200)
        self._Delay_FM_win = RangeWidget(self._Delay_FM_range, self.set_Delay_FM, 'Delay_FM', "counter_slider", float)
        self.top_grid_layout.addWidget(self._Delay_FM_win, 6, 4, 1, 1)
        for r in range(6, 7):
            self.top_grid_layout.setRowStretch(r, 1)
        for c in range(4, 5):
            self.top_grid_layout.setColumnStretch(c, 1)
        self._Delay_AM_range = Range(0, 400, 1, 0, 200)
        self._Delay_AM_win = RangeWidget(self._Delay_AM_range, self.set_Delay_AM, 'Delay_AM', "counter_slider", float)
        self.top_grid_layout.addWidget(self._Delay_AM_win, 5, 4, 1, 1)
        for r in range(5, 6):
            self.top_grid_layout.setRowStretch(r, 1)
        for c in range(4, 5):
            self.top_grid_layout.setColumnStretch(c, 1)
        self._A_range = Range(0, 1, 0.1, 0.5, 200)
        self._A_win = RangeWidget(self._A_range, self.set_A, 'A', "counter_slider", float)
        self.top_grid_layout.addWidget(self._A_win, 1, 4, 1, 1)
        for r in range(1, 2):
            self.top_grid_layout.setRowStretch(r, 1)
        for c in range(4, 5):
            self.top_grid_layout.setColumnStretch(c, 1)
        self.qtgui_time_sink_x_3 = qtgui.time_sink_f(
            1024, #size
            samp_rate, #samp_rate
            'Pot Ruído IN', #name
            2 #number of inputs
        )
        self.qtgui_time_sink_x_3.set_update_time(0.10)
        self.qtgui_time_sink_x_3.set_y_axis(-1, 1)

        self.qtgui_time_sink_x_3.set_y_label('Amplitude', "")

        self.qtgui_time_sink_x_3.enable_tags(True)
        self.qtgui_time_sink_x_3.set_trigger_mode(qtgui.TRIG_MODE_AUTO, qtgui.TRIG_SLOPE_POS, 0.0, 0, 0, "")
        self.qtgui_time_sink_x_3.enable_autoscale(False)
        self.qtgui_time_sink_x_3.enable_grid(True)
        self.qtgui_time_sink_x_3.enable_axis_labels(True)
        self.qtgui_time_sink_x_3.enable_control_panel(False)
        self.qtgui_time_sink_x_3.enable_stem_plot(False)


        labels = ['AM', 'FM', 'Signal 3', 'Signal 4', 'Signal 5',
            'Signal 6', 'Signal 7', 'Signal 8', 'Signal 9', 'Signal 10']
        widths = [1, 1, 1, 1, 1,
            1, 1, 1, 1, 1]
        colors = ['blue', 'red', 'green', 'black', 'cyan',
            'magenta', 'yellow', 'dark red', 'dark green', 'dark blue']
        alphas = [1.0, 1.0, 1.0, 1.0, 1.0,
            1.0, 1.0, 1.0, 1.0, 1.0]
        styles = [1, 1, 1, 1, 1,
            1, 1, 1, 1, 1]
        markers = [-1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1]


        for i in range(2):
            if len(labels[i]) == 0:
                self.qtgui_time_sink_x_3.set_line_label(i, "Data {0}".format(i))
            else:
                self.qtgui_time_sink_x_3.set_line_label(i, labels[i])
            self.qtgui_time_sink_x_3.set_line_width(i, widths[i])
            self.qtgui_time_sink_x_3.set_line_color(i, colors[i])
            self.qtgui_time_sink_x_3.set_line_style(i, styles[i])
            self.qtgui_time_sink_x_3.set_line_marker(i, markers[i])
            self.qtgui_time_sink_x_3.set_line_alpha(i, alphas[i])

        self._qtgui_time_sink_x_3_win = sip.wrapinstance(self.qtgui_time_sink_x_3.pyqwidget(), Qt.QWidget)
        self.top_grid_layout.addWidget(self._qtgui_time_sink_x_3_win, 1, 3, 3, 1)
        for r in range(1, 4):
            self.top_grid_layout.setRowStretch(r, 1)
        for c in range(3, 4):
            self.top_grid_layout.setColumnStretch(c, 1)
        self.qtgui_time_sink_x_2 = qtgui.time_sink_f(
            1024, #size
            samp_rate, #samp_rate
            'RSR IN', #name
            2 #number of inputs
        )
        self.qtgui_time_sink_x_2.set_update_time(0.10)
        self.qtgui_time_sink_x_2.set_y_axis(-1, 1)

        self.qtgui_time_sink_x_2.set_y_label('Amplitude', 'V')

        self.qtgui_time_sink_x_2.enable_tags(True)
        self.qtgui_time_sink_x_2.set_trigger_mode(qtgui.TRIG_MODE_AUTO, qtgui.TRIG_SLOPE_POS, 0.0, 0, 0, "")
        self.qtgui_time_sink_x_2.enable_autoscale(False)
        self.qtgui_time_sink_x_2.enable_grid(True)
        self.qtgui_time_sink_x_2.enable_axis_labels(True)
        self.qtgui_time_sink_x_2.enable_control_panel(False)
        self.qtgui_time_sink_x_2.enable_stem_plot(False)


        labels = ['AM', 'FM', 'Signal 3', 'Signal 4', 'Signal 5',
            'Signal 6', 'Signal 7', 'Signal 8', 'Signal 9', 'Signal 10']
        widths = [1, 1, 1, 1, 1,
            1, 1, 1, 1, 1]
        colors = ['blue', 'red', 'green', 'black', 'cyan',
            'magenta', 'yellow', 'dark red', 'dark green', 'dark blue']
        alphas = [1.0, 1.0, 1.0, 1.0, 1.0,
            1.0, 1.0, 1.0, 1.0, 1.0]
        styles = [1, 1, 1, 1, 1,
            1, 1, 1, 1, 1]
        markers = [-1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1]


        for i in range(2):
            if len(labels[i]) == 0:
                self.qtgui_time_sink_x_2.set_line_label(i, "Data {0}".format(i))
            else:
                self.qtgui_time_sink_x_2.set_line_label(i, labels[i])
            self.qtgui_time_sink_x_2.set_line_width(i, widths[i])
            self.qtgui_time_sink_x_2.set_line_color(i, colors[i])
            self.qtgui_time_sink_x_2.set_line_style(i, styles[i])
            self.qtgui_time_sink_x_2.set_line_marker(i, markers[i])
            self.qtgui_time_sink_x_2.set_line_alpha(i, alphas[i])

        self._qtgui_time_sink_x_2_win = sip.wrapinstance(self.qtgui_time_sink_x_2.pyqwidget(), Qt.QWidget)
        self.top_grid_layout.addWidget(self._qtgui_time_sink_x_2_win, 4, 2, 3, 1)
        for r in range(4, 7):
            self.top_grid_layout.setRowStretch(r, 1)
        for c in range(2, 3):
            self.top_grid_layout.setColumnStretch(c, 1)
        self.qtgui_time_sink_x_1 = qtgui.time_sink_f(
            1024, #size
            samp_rate, #samp_rate
            'RSR OUT', #name
            2 #number of inputs
        )
        self.qtgui_time_sink_x_1.set_update_time(0.10)
        self.qtgui_time_sink_x_1.set_y_axis(-1, 1)

        self.qtgui_time_sink_x_1.set_y_label('Amplitude', 'V')

        self.qtgui_time_sink_x_1.enable_tags(True)
        self.qtgui_time_sink_x_1.set_trigger_mode(qtgui.TRIG_MODE_AUTO, qtgui.TRIG_SLOPE_POS, 0.0, 0, 0, "")
        self.qtgui_time_sink_x_1.enable_autoscale(False)
        self.qtgui_time_sink_x_1.enable_grid(True)
        self.qtgui_time_sink_x_1.enable_axis_labels(True)
        self.qtgui_time_sink_x_1.enable_control_panel(False)
        self.qtgui_time_sink_x_1.enable_stem_plot(False)


        labels = ['AM', 'FM', 'Signal 3', 'Signal 4', 'Signal 5',
            'Signal 6', 'Signal 7', 'Signal 8', 'Signal 9', 'Signal 10']
        widths = [1, 1, 1, 1, 1,
            1, 1, 1, 1, 1]
        colors = ['blue', 'red', 'green', 'black', 'cyan',
            'magenta', 'yellow', 'dark red', 'dark green', 'dark blue']
        alphas = [1.0, 1.0, 1.0, 1.0, 1.0,
            1.0, 1.0, 1.0, 1.0, 1.0]
        styles = [1, 1, 1, 1, 1,
            1, 1, 1, 1, 1]
        markers = [-1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1]


        for i in range(2):
            if len(labels[i]) == 0:
                self.qtgui_time_sink_x_1.set_line_label(i, "Data {0}".format(i))
            else:
                self.qtgui_time_sink_x_1.set_line_label(i, labels[i])
            self.qtgui_time_sink_x_1.set_line_width(i, widths[i])
            self.qtgui_time_sink_x_1.set_line_color(i, colors[i])
            self.qtgui_time_sink_x_1.set_line_style(i, styles[i])
            self.qtgui_time_sink_x_1.set_line_marker(i, markers[i])
            self.qtgui_time_sink_x_1.set_line_alpha(i, alphas[i])

        self._qtgui_time_sink_x_1_win = sip.wrapinstance(self.qtgui_time_sink_x_1.pyqwidget(), Qt.QWidget)
        self.top_grid_layout.addWidget(self._qtgui_time_sink_x_1_win, 4, 1, 3, 1)
        for r in range(4, 7):
            self.top_grid_layout.setRowStretch(r, 1)
        for c in range(1, 2):
            self.top_grid_layout.setColumnStretch(c, 1)
        self.qtgui_time_sink_x_0 = qtgui.time_sink_f(
            1024, #size
            samp_rate, #samp_rate
            'Osciloscópio', #name
            3 #number of inputs
        )
        self.qtgui_time_sink_x_0.set_update_time(0.10)
        self.qtgui_time_sink_x_0.set_y_axis(-1, 1)

        self.qtgui_time_sink_x_0.set_y_label('Amplitude', "")

        self.qtgui_time_sink_x_0.enable_tags(True)
        self.qtgui_time_sink_x_0.set_trigger_mode(qtgui.TRIG_MODE_AUTO, qtgui.TRIG_SLOPE_POS, 0.0, 0, 0, "")
        self.qtgui_time_sink_x_0.enable_autoscale(False)
        self.qtgui_time_sink_x_0.enable_grid(True)
        self.qtgui_time_sink_x_0.enable_axis_labels(True)
        self.qtgui_time_sink_x_0.enable_control_panel(False)
        self.qtgui_time_sink_x_0.enable_stem_plot(False)


        labels = ['Demod_DSB', 'Demod_FM', 'Mensagem', 'Signal 4', 'Signal 5',
            'Signal 6', 'Signal 7', 'Signal 8', 'Signal 9', 'Signal 10']
        widths = [1, 1, 1, 1, 1,
            1, 1, 1, 1, 1]
        colors = ['blue', 'red', 'green', 'black', 'cyan',
            'magenta', 'yellow', 'dark red', 'dark green', 'dark blue']
        alphas = [1.0, 1.0, 1.0, 1.0, 1.0,
            1.0, 1.0, 1.0, 1.0, 1.0]
        styles = [1, 1, 1, 1, 1,
            1, 1, 1, 1, 1]
        markers = [-1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1]


        for i in range(3):
            if len(labels[i]) == 0:
                self.qtgui_time_sink_x_0.set_line_label(i, "Data {0}".format(i))
            else:
                self.qtgui_time_sink_x_0.set_line_label(i, labels[i])
            self.qtgui_time_sink_x_0.set_line_width(i, widths[i])
            self.qtgui_time_sink_x_0.set_line_color(i, colors[i])
            self.qtgui_time_sink_x_0.set_line_style(i, styles[i])
            self.qtgui_time_sink_x_0.set_line_marker(i, markers[i])
            self.qtgui_time_sink_x_0.set_line_alpha(i, alphas[i])

        self._qtgui_time_sink_x_0_win = sip.wrapinstance(self.qtgui_time_sink_x_0.pyqwidget(), Qt.QWidget)
        self.top_grid_layout.addWidget(self._qtgui_time_sink_x_0_win, 1, 1, 3, 2)
        for r in range(1, 4):
            self.top_grid_layout.setRowStretch(r, 1)
        for c in range(1, 3):
            self.top_grid_layout.setColumnStretch(c, 1)
        self.qtgui_const_sink_x_0 = qtgui.const_sink_c(
            1024, #size
            "", #name
            2 #number of inputs
        )
        self.qtgui_const_sink_x_0.set_update_time(0.10)
        self.qtgui_const_sink_x_0.set_y_axis(-2, 2)
        self.qtgui_const_sink_x_0.set_x_axis(-2, 2)
        self.qtgui_const_sink_x_0.set_trigger_mode(qtgui.TRIG_MODE_AUTO, qtgui.TRIG_SLOPE_POS, 0.0, 0, "")
        self.qtgui_const_sink_x_0.enable_autoscale(False)
        self.qtgui_const_sink_x_0.enable_grid(True)
        self.qtgui_const_sink_x_0.enable_axis_labels(True)


        labels = ['FM', 'AM', '', '', '',
            '', '', '', '', '']
        widths = [1, 1, 1, 1, 1,
            1, 1, 1, 1, 1]
        colors = ["blue", "red", "red", "red", "red",
            "red", "red", "red", "red", "red"]
        styles = [0, 0, 0, 0, 0,
            0, 0, 0, 0, 0]
        markers = [0, 0, 0, 0, 0,
            0, 0, 0, 0, 0]
        alphas = [1.0, 1.0, 1.0, 1.0, 1.0,
            1.0, 1.0, 1.0, 1.0, 1.0]

        for i in range(2):
            if len(labels[i]) == 0:
                self.qtgui_const_sink_x_0.set_line_label(i, "Data {0}".format(i))
            else:
                self.qtgui_const_sink_x_0.set_line_label(i, labels[i])
            self.qtgui_const_sink_x_0.set_line_width(i, widths[i])
            self.qtgui_const_sink_x_0.set_line_color(i, colors[i])
            self.qtgui_const_sink_x_0.set_line_style(i, styles[i])
            self.qtgui_const_sink_x_0.set_line_marker(i, markers[i])
            self.qtgui_const_sink_x_0.set_line_alpha(i, alphas[i])

        self._qtgui_const_sink_x_0_win = sip.wrapinstance(self.qtgui_const_sink_x_0.pyqwidget(), Qt.QWidget)
        self.top_grid_layout.addWidget(self._qtgui_const_sink_x_0_win, 4, 3, 3, 1)
        for r in range(4, 7):
            self.top_grid_layout.setRowStretch(r, 1)
        for c in range(3, 4):
            self.top_grid_layout.setColumnStretch(c, 1)
        self.low_pass_filter_1 = filter.fir_filter_fff(
            1,
            firdes.low_pass(
                1,
                samp_rate,
                11000,
                100,
                firdes.WIN_HAMMING,
                6.76))
        self.low_pass_filter_0 = filter.fir_filter_fff(
            1,
            firdes.low_pass(
                1,
                samp_rate,
                11000,
                100,
                firdes.WIN_HAMMING,
                6.76))
        self.dc_blocker_xx_0 = filter.dc_blocker_ff(400, True)
        self.blocks_vco_c_0 = blocks.vco_c(samp_rate, 8000*2*pi, 1)
        self.blocks_throttle_1 = blocks.throttle(gr.sizeof_gr_complex*1, samp_rate,True)
        self.blocks_throttle_0 = blocks.throttle(gr.sizeof_gr_complex*1, samp_rate,True)
        self.blocks_sub_xx_0_0 = blocks.sub_ff(1)
        self.blocks_sub_xx_0 = blocks.sub_ff(1)
        self.blocks_rms_xx_2_0 = blocks.rms_ff(0.0001)
        self.blocks_rms_xx_2 = blocks.rms_ff(0.0001)
        self.blocks_rms_xx_1 = blocks.rms_ff(0.0001)
        self.blocks_rms_xx_0_1 = blocks.rms_cf(0.0001)
        self.blocks_rms_xx_0_0_0 = blocks.rms_cf(0.0001)
        self.blocks_rms_xx_0_0 = blocks.rms_ff(0.0001)
        self.blocks_rms_xx_0 = blocks.rms_ff(0.0001)
        self.blocks_null_sink_0 = blocks.null_sink(gr.sizeof_gr_complex*1)
        self.blocks_nlog10_ff_3 = blocks.nlog10_ff(1, 1, 0)
        self.blocks_nlog10_ff_2 = blocks.nlog10_ff(1, 1, 0)
        self.blocks_nlog10_ff_1 = blocks.nlog10_ff(1, 1, 0)
        self.blocks_nlog10_ff_0_1 = blocks.nlog10_ff(1, 1, 0)
        self.blocks_nlog10_ff_0_0 = blocks.nlog10_ff(1, 1, 0)
        self.blocks_nlog10_ff_0 = blocks.nlog10_ff(1, 1, 0)
        self.blocks_multiply_xx_1 = blocks.multiply_vcc(1)
        self.blocks_multiply_xx_0 = blocks.multiply_vff(1)
        self.blocks_multiply_const_vxx_2 = blocks.multiply_const_ff(3.97888)
        self.blocks_multiply_const_vxx_1 = blocks.multiply_const_ff(G_demod_AM)
        self.blocks_multiply_const_vxx_0_0 = blocks.multiply_const_cc(G_ruido_FM)
        self.blocks_multiply_const_vxx_0 = blocks.multiply_const_ff(G_ruido_AM)
        self.blocks_float_to_complex_0_0 = blocks.float_to_complex(1)
        self.blocks_float_to_complex_0 = blocks.float_to_complex(1)
        self.blocks_divide_xx_1_0 = blocks.divide_ff(1)
        self.blocks_divide_xx_1 = blocks.divide_ff(1)
        self.blocks_divide_xx_0_0 = blocks.divide_ff(1)
        self.blocks_divide_xx_0 = blocks.divide_ff(1)
        self.blocks_delay_0_0 = blocks.delay(gr.sizeof_float*1, Delay_FM)
        self.blocks_delay_0 = blocks.delay(gr.sizeof_float*1, Delay_AM)
        self.blocks_complex_to_real_1 = blocks.complex_to_real(1)
        self.blocks_complex_to_real_0 = blocks.complex_to_real(1)
        self.blocks_add_xx_1 = blocks.add_vcc(1)
        self.blocks_add_xx_0 = blocks.add_vff(1)
        self.blocks_add_const_vxx_1 = blocks.add_const_ff(-1.57075)
        self.blocks_add_const_vxx_0 = blocks.add_const_ff(1)
        self.blocks_abs_xx_0 = blocks.abs_ff(1)
        self.band_pass_filter_1_0 = filter.fir_filter_ccf(
            1,
            firdes.band_pass(
                1,
                samp_rate,
                36000,
                64000,
                100,
                firdes.WIN_HAMMING,
                6.76))
        self.band_pass_filter_1 = filter.fir_filter_fff(
            1,
            firdes.band_pass(
                1,
                samp_rate,
                36000,
                64000,
                100,
                firdes.WIN_HAMMING,
                6.76))
        self.band_pass_filter_0 = filter.fir_filter_fff(
            1,
            firdes.band_pass(
                1,
                samp_rate,
                100,
                11000,
                100,
                firdes.WIN_HAMMING,
                6.76))
        self.analog_sig_source_x_0_0 = analog.sig_source_c(samp_rate, analog.GR_COS_WAVE, 50000, 1, 0, 0)
        self.analog_sig_source_x_0 = analog.sig_source_f(samp_rate, analog.GR_SQR_WAVE, 500, 2*A, -A, 0)
        self.analog_pll_freqdet_cf_0 = analog.pll_freqdet_cf(0.06283, 2.01056, 1.13094)
        self.analog_noise_source_x_0 = analog.noise_source_c(analog.GR_GAUSSIAN, 1, 0)



        ##################################################
        # Connections
        ##################################################
        self.connect((self.analog_noise_source_x_0, 0), (self.blocks_throttle_0, 0))
        self.connect((self.analog_pll_freqdet_cf_0, 0), (self.blocks_add_const_vxx_1, 0))
        self.connect((self.analog_sig_source_x_0, 0), (self.band_pass_filter_0, 0))
        self.connect((self.analog_sig_source_x_0_0, 0), (self.blocks_throttle_1, 0))
        self.connect((self.band_pass_filter_0, 0), (self.blocks_add_const_vxx_0, 0))
        self.connect((self.band_pass_filter_0, 0), (self.blocks_rms_xx_1, 0))
        self.connect((self.band_pass_filter_0, 0), (self.blocks_sub_xx_0, 1))
        self.connect((self.band_pass_filter_0, 0), (self.blocks_sub_xx_0_0, 1))
        self.connect((self.band_pass_filter_0, 0), (self.blocks_vco_c_0, 0))
        self.connect((self.band_pass_filter_0, 0), (self.qtgui_time_sink_x_0, 2))
        self.connect((self.band_pass_filter_1, 0), (self.blocks_rms_xx_0_0, 0))
        self.connect((self.band_pass_filter_1_0, 0), (self.blocks_rms_xx_0_0_0, 0))
        self.connect((self.blocks_abs_xx_0, 0), (self.low_pass_filter_0, 0))
        self.connect((self.blocks_add_const_vxx_0, 0), (self.blocks_multiply_xx_0, 0))
        self.connect((self.blocks_add_const_vxx_1, 0), (self.blocks_multiply_const_vxx_2, 0))
        self.connect((self.blocks_add_xx_0, 0), (self.blocks_abs_xx_0, 0))
        self.connect((self.blocks_add_xx_1, 0), (self.analog_pll_freqdet_cf_0, 0))
        self.connect((self.blocks_complex_to_real_0, 0), (self.blocks_multiply_const_vxx_0, 0))
        self.connect((self.blocks_complex_to_real_1, 0), (self.blocks_multiply_xx_0, 1))
        self.connect((self.blocks_delay_0, 0), (self.blocks_sub_xx_0, 0))
        self.connect((self.blocks_delay_0, 0), (self.qtgui_time_sink_x_0, 0))
        self.connect((self.blocks_delay_0_0, 0), (self.blocks_sub_xx_0_0, 0))
        self.connect((self.blocks_delay_0_0, 0), (self.qtgui_time_sink_x_0, 1))
        self.connect((self.blocks_divide_xx_0, 0), (self.blocks_nlog10_ff_0_1, 0))
        self.connect((self.blocks_divide_xx_0_0, 0), (self.blocks_nlog10_ff_1, 0))
        self.connect((self.blocks_divide_xx_1, 0), (self.blocks_nlog10_ff_0, 0))
        self.connect((self.blocks_divide_xx_1_0, 0), (self.blocks_nlog10_ff_0_0, 0))
        self.connect((self.blocks_float_to_complex_0, 0), (self.qtgui_const_sink_x_0, 0))
        self.connect((self.blocks_float_to_complex_0_0, 0), (self.qtgui_const_sink_x_0, 1))
        self.connect((self.blocks_multiply_const_vxx_0, 0), (self.band_pass_filter_1, 0))
        self.connect((self.blocks_multiply_const_vxx_0, 0), (self.blocks_add_xx_0, 0))
        self.connect((self.blocks_multiply_const_vxx_0_0, 0), (self.band_pass_filter_1_0, 0))
        self.connect((self.blocks_multiply_const_vxx_0_0, 0), (self.blocks_add_xx_1, 0))
        self.connect((self.blocks_multiply_const_vxx_1, 0), (self.blocks_delay_0, 0))
        self.connect((self.blocks_multiply_const_vxx_2, 0), (self.low_pass_filter_1, 0))
        self.connect((self.blocks_multiply_xx_0, 0), (self.blocks_add_xx_0, 1))
        self.connect((self.blocks_multiply_xx_0, 0), (self.blocks_rms_xx_0, 0))
        self.connect((self.blocks_multiply_xx_1, 0), (self.blocks_add_xx_1, 1))
        self.connect((self.blocks_multiply_xx_1, 0), (self.blocks_rms_xx_0_1, 0))
        self.connect((self.blocks_nlog10_ff_0, 0), (self.blocks_float_to_complex_0_0, 1))
        self.connect((self.blocks_nlog10_ff_0, 0), (self.qtgui_time_sink_x_1, 0))
        self.connect((self.blocks_nlog10_ff_0_0, 0), (self.blocks_float_to_complex_0, 1))
        self.connect((self.blocks_nlog10_ff_0_0, 0), (self.qtgui_time_sink_x_1, 1))
        self.connect((self.blocks_nlog10_ff_0_1, 0), (self.blocks_float_to_complex_0_0, 0))
        self.connect((self.blocks_nlog10_ff_0_1, 0), (self.qtgui_time_sink_x_2, 0))
        self.connect((self.blocks_nlog10_ff_1, 0), (self.blocks_float_to_complex_0, 0))
        self.connect((self.blocks_nlog10_ff_1, 0), (self.qtgui_time_sink_x_2, 1))
        self.connect((self.blocks_nlog10_ff_2, 0), (self.qtgui_time_sink_x_3, 0))
        self.connect((self.blocks_nlog10_ff_3, 0), (self.qtgui_time_sink_x_3, 1))
        self.connect((self.blocks_rms_xx_0, 0), (self.blocks_divide_xx_0, 0))
        self.connect((self.blocks_rms_xx_0_0, 0), (self.blocks_divide_xx_0, 1))
        self.connect((self.blocks_rms_xx_0_0, 0), (self.blocks_nlog10_ff_2, 0))
        self.connect((self.blocks_rms_xx_0_0_0, 0), (self.blocks_divide_xx_0_0, 1))
        self.connect((self.blocks_rms_xx_0_0_0, 0), (self.blocks_nlog10_ff_3, 0))
        self.connect((self.blocks_rms_xx_0_1, 0), (self.blocks_divide_xx_0_0, 0))
        self.connect((self.blocks_rms_xx_1, 0), (self.blocks_divide_xx_1, 0))
        self.connect((self.blocks_rms_xx_1, 0), (self.blocks_divide_xx_1_0, 0))
        self.connect((self.blocks_rms_xx_2, 0), (self.blocks_divide_xx_1, 1))
        self.connect((self.blocks_rms_xx_2_0, 0), (self.blocks_divide_xx_1_0, 1))
        self.connect((self.blocks_sub_xx_0, 0), (self.blocks_rms_xx_2, 0))
        self.connect((self.blocks_sub_xx_0_0, 0), (self.blocks_rms_xx_2_0, 0))
        self.connect((self.blocks_throttle_0, 0), (self.blocks_complex_to_real_0, 0))
        self.connect((self.blocks_throttle_0, 0), (self.blocks_multiply_const_vxx_0_0, 0))
        self.connect((self.blocks_throttle_0, 0), (self.blocks_null_sink_0, 0))
        self.connect((self.blocks_throttle_1, 0), (self.blocks_complex_to_real_1, 0))
        self.connect((self.blocks_throttle_1, 0), (self.blocks_multiply_xx_1, 1))
        self.connect((self.blocks_vco_c_0, 0), (self.blocks_multiply_xx_1, 0))
        self.connect((self.dc_blocker_xx_0, 0), (self.blocks_multiply_const_vxx_1, 0))
        self.connect((self.low_pass_filter_0, 0), (self.dc_blocker_xx_0, 0))
        self.connect((self.low_pass_filter_1, 0), (self.blocks_delay_0_0, 0))

    def closeEvent(self, event):
        self.settings = Qt.QSettings("GNU Radio", "m180108140_Exp06_AR02")
        self.settings.setValue("geometry", self.saveGeometry())
        event.accept()

    def get_samp_rate(self):
        return self.samp_rate

    def set_samp_rate(self, samp_rate):
        self.samp_rate = samp_rate
        self.analog_sig_source_x_0.set_sampling_freq(self.samp_rate)
        self.analog_sig_source_x_0_0.set_sampling_freq(self.samp_rate)
        self.band_pass_filter_0.set_taps(firdes.band_pass(1, self.samp_rate, 100, 11000, 100, firdes.WIN_HAMMING, 6.76))
        self.band_pass_filter_1.set_taps(firdes.band_pass(1, self.samp_rate, 36000, 64000, 100, firdes.WIN_HAMMING, 6.76))
        self.band_pass_filter_1_0.set_taps(firdes.band_pass(1, self.samp_rate, 36000, 64000, 100, firdes.WIN_HAMMING, 6.76))
        self.blocks_throttle_0.set_sample_rate(self.samp_rate)
        self.blocks_throttle_1.set_sample_rate(self.samp_rate)
        self.low_pass_filter_0.set_taps(firdes.low_pass(1, self.samp_rate, 11000, 100, firdes.WIN_HAMMING, 6.76))
        self.low_pass_filter_1.set_taps(firdes.low_pass(1, self.samp_rate, 11000, 100, firdes.WIN_HAMMING, 6.76))
        self.qtgui_time_sink_x_0.set_samp_rate(self.samp_rate)
        self.qtgui_time_sink_x_1.set_samp_rate(self.samp_rate)
        self.qtgui_time_sink_x_2.set_samp_rate(self.samp_rate)
        self.qtgui_time_sink_x_3.set_samp_rate(self.samp_rate)

    def get_pi(self):
        return self.pi

    def set_pi(self, pi):
        self.pi = pi

    def get_G_ruido_FM(self):
        return self.G_ruido_FM

    def set_G_ruido_FM(self, G_ruido_FM):
        self.G_ruido_FM = G_ruido_FM
        self.blocks_multiply_const_vxx_0_0.set_k(self.G_ruido_FM)

    def get_G_ruido_AM(self):
        return self.G_ruido_AM

    def set_G_ruido_AM(self, G_ruido_AM):
        self.G_ruido_AM = G_ruido_AM
        self.blocks_multiply_const_vxx_0.set_k(self.G_ruido_AM)

    def get_G_demod_AM(self):
        return self.G_demod_AM

    def set_G_demod_AM(self, G_demod_AM):
        self.G_demod_AM = G_demod_AM
        self.blocks_multiply_const_vxx_1.set_k(self.G_demod_AM)

    def get_Delay_FM(self):
        return self.Delay_FM

    def set_Delay_FM(self, Delay_FM):
        self.Delay_FM = Delay_FM
        self.blocks_delay_0_0.set_dly(self.Delay_FM)

    def get_Delay_AM(self):
        return self.Delay_AM

    def set_Delay_AM(self, Delay_AM):
        self.Delay_AM = Delay_AM
        self.blocks_delay_0.set_dly(self.Delay_AM)

    def get_A(self):
        return self.A

    def set_A(self, A):
        self.A = A
        self.analog_sig_source_x_0.set_amplitude(2*self.A)
        self.analog_sig_source_x_0.set_offset(-self.A)



def main(top_block_cls=m180108140_Exp06_AR02, options=None):

    if StrictVersion("4.5.0") <= StrictVersion(Qt.qVersion()) < StrictVersion("5.0.0"):
        style = gr.prefs().get_string('qtgui', 'style', 'raster')
        Qt.QApplication.setGraphicsSystem(style)
    qapp = Qt.QApplication(sys.argv)

    tb = top_block_cls()
    tb.start()
    tb.show()

    def sig_handler(sig=None, frame=None):
        Qt.QApplication.quit()

    signal.signal(signal.SIGINT, sig_handler)
    signal.signal(signal.SIGTERM, sig_handler)

    timer = Qt.QTimer()
    timer.start(500)
    timer.timeout.connect(lambda: None)

    def quitting():
        tb.stop()
        tb.wait()
    qapp.aboutToQuit.connect(quitting)
    qapp.exec_()


if __name__ == '__main__':
    main()