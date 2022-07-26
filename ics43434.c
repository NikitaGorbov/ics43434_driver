// SPDX-License-Identifier: GPL-2.0-only
/*
 * I2S MEMS microphone driver for InvenSense ICS-43432 and similar
 * MEMS-based microphones.
 *
 * - Non configurable.
 * - I2S interface, 64 BCLs per frame, 32 bits per channel, 24 bit data
 *
 * Copyright (c) 2015 Axis Communications AB
 */

/* 
	Modified driver for ics43432
*/

#include <linux/module.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/of_platform.h>
#include <sound/core.h>
#include <sound/pcm.h>
#include <sound/pcm_params.h>
#include <sound/soc.h>
#include <sound/initval.h>
#include <sound/tlv.h>

#define ICS43434_RATE_MIN 6250 /* Hz, from data sheet, low power mode */
#define ICS43434_RATE_MAX 51600  /* Hz, from data sheet, low power mode */

#define ICS43434_FORMATS (SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S32)

static struct snd_soc_dai_driver ics43434_dai = {
	.name = "ics43434-hifi",
	.capture = {
		.stream_name = "Capture",
		.channels_min = 1,
		.channels_max = 2,
		.rate_min = ICS43434_RATE_MIN,
		.rate_max = ICS43434_RATE_MAX,
		.rates = SNDRV_PCM_RATE_CONTINUOUS,
		.formats = ICS43434_FORMATS,
	},
};

static const struct snd_soc_component_driver ics43434_component_driver = {
	.idle_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
};

static int ics43434_probe(struct platform_device *pdev)
{
	/*
	struct device_node *cpu_np, *np = pdev->dev.of_node;
	struct platform_device *cpu_pdev;
	cpu_np = of_parse_phandle(np, "cpu-dai", 0);
	 if (!cpu_np) {
        dev_err(&pdev->dev, "cpu dai phandle missing or invalid\n");
        return -EINVAL;
    }
    cpu_pdev = of_find_device_by_node(cpu_np);
    if (!cpu_pdev) {
        dev_err(&pdev->dev, "failed to find SAI platform device\n");
		return -EINVAL;
	}
	*/
    printk(KERN_INFO "ics43434 probe successful\n");
	return devm_snd_soc_register_component(&pdev->dev,
			&ics43434_component_driver,
			&ics43434_dai, 1);
}

static const struct of_device_id ics43434_ids[] = {
	{ .compatible = "invensense,ics43434", },
	{ }
};
MODULE_DEVICE_TABLE(of, ics43434_ids);

static struct platform_driver ics43434_driver = {
	.driver = {
		.name = "ics43434",
		.of_match_table = of_match_ptr(ics43434_ids),
	},
	.probe = ics43434_probe,
};

module_platform_driver(ics43434_driver);

MODULE_DESCRIPTION("ASoC ICS43434 driver");
MODULE_AUTHOR("Ricard Wanderlof <ricardw@axis.com>");
MODULE_LICENSE("GPL v2");