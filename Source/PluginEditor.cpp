/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
YellowRoseAudioProcessorEditor::YellowRoseAudioProcessorEditor (YellowRoseAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    mLoadButton.onClick = [&]() { audioProcessor.loadFile(); };
    addAndMakeVisible(mLoadButton);
    
    setSize(600, 200);
}

YellowRoseAudioProcessorEditor::~YellowRoseAudioProcessorEditor()
{
}

//==============================================================================
void YellowRoseAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    //g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    //g.setColour (juce::Colours::white);
    //g.setFont (juce::FontOptions (15.0f));
    //g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);\

    g.fillAll(juce::Colours::grey);
    g.setColour(juce::Colours::yellow);

    if (mShouldBePainting) {
        juce::Path p;
        mAudioPoints.clear();

        auto waveform = audioProcessor.getWaveForm();
        auto ratio = waveform.getNumSamples() / getWidth();
        auto buffer = waveform.getReadPointer(0);

        //scale audio on x axis
        for (int sample = 0; sample < waveform.getNumSamples(); sample += ratio) {
            mAudioPoints.push_back(buffer[sample]);
        }

        p.startNewSubPath(0, getHeight() / 2);

        //scale audio on y axis
        for (int sample = 0; sample < mAudioPoints.size(); ++sample) {
            auto point = juce::jmap<float>(mAudioPoints[sample], -1.0f, 1.0f, 200, 0);
            p.lineTo(sample, point);
        }

        g.strokePath(p, juce::PathStrokeType(2));

        mShouldBePainting = false;
    }

    /*if (audioProcessor.getNumSamplerSounds() > 0) {
        g.fillAll(juce::Colours::red);

        g.setColour(juce::Colours::white);
        g.setFont(15.0f);
        g.drawText("Sample Loaded", getLocalBounds(), juce::Justification::centred, true);
    }
    else {
        g.setColour(juce::Colours::white);
        g.setFont(15.0f);
        g.drawText("Load a sound", getLocalBounds(), juce::Justification::centred, true);
    }*/
}

void YellowRoseAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    //mLoadButton.setBounds(150, 100, 100, 100);


}

bool YellowRoseAudioProcessorEditor::isInterestedInFileDrag(const juce::StringArray& files)
{
    for (auto file : files) {
        if (file.contains(".wav") || file.contains(".mp3") || file.contains(".aif") || file.contains(".flac")) {
            return true;
        }
    }

    return false;
}

void YellowRoseAudioProcessorEditor::filesDropped(const juce::StringArray& files, int x, int y)
{
    for (auto file : files) {
        if (isInterestedInFileDrag(file)) {
            audioProcessor.loadFile(file);  
            mShouldBePainting = true;
            repaint();
        }
    }
}