#include <gst/gst.h>

#ifdef __APPLE__
#include <TargetConditionals.h>
#endif

static void enable_factory(const gchar *name, gboolean enable)
{
    GstRegistry *registry = NULL;
    GstElementFactory *factory = NULL;

    registry = gst_registry_get_default();
    if (!registry) return;

    factory = gst_element_factory_find(name);
    if (!factory) return;

    if (enable) {
        gst_plugin_feature_set_rank(GST_PLUGIN_FEATURE(factory), GST_RANK_PRIMARY + 1);
    } else {
        gst_plugin_feature_set_rank(GST_PLUGIN_FEATURE(factory), GST_RANK_NONE);
    }

    gst_registry_add_feature(registry, GST_PLUGIN_FEATURE(factory));
    return;
}

int tutorial_main(int argc, char *argv[])
{
    enable_factory("vaapi", 0);

    GstElement *pipeline;
    GstBus *bus;
    GstMessage *msg;

    /* Initialize GStreamer */
    gst_init(&argc, &argv);

    /* Build the pipeline */
    pipeline =
        gst_parse_launch("playbin uri=file:///home/aniu/Videos/SilentHill2Promise_ThemeofLaura.mp4",
                         NULL);

    /* Start playing */
    gst_element_set_state(pipeline, GST_STATE_PLAYING);

    /* Wait until error or EOS */
    bus = gst_element_get_bus(pipeline);
    msg =
        gst_bus_timed_pop_filtered(bus, GST_CLOCK_TIME_NONE,
                                   GST_MESSAGE_ERROR | GST_MESSAGE_EOS);

    /* See next tutorial for proper error message handling/parsing */
    if (GST_MESSAGE_TYPE(msg) == GST_MESSAGE_ERROR) {
        g_error(
            "An error occurred! Re-run with the GST_DEBUG=*:WARN environment "
            "variable set for more details.");
    }

    /* Free resources */
    gst_message_unref(msg);
    gst_object_unref(bus);
    gst_element_set_state(pipeline, GST_STATE_NULL);
    gst_object_unref(pipeline);
    return 0;
}

int main(int argc, char *argv[])
{
#if defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE
    return gst_macos_main(tutorial_main, argc, argv, NULL);
#else
    return tutorial_main(argc, argv);
#endif
}
