import React from 'react'
import Image from 'next/image'
import fs from 'fs'
import { Splide, SplideSlide } from '@splidejs/react-splide'
import setting from '../setting'

interface Props {
  imageFilePaths: string[]
}

export default function Home (props: Props): React.JSX.Element {
  const { imageFilePaths } = props

  return (
    <>
      <div id='Museum'>
        <Splide
          options={{
            type: 'loop',
            perPage: 1
          }}
          className='d-block m-auto mw-100'
          style={{
            width: `${setting.imageSize}px`
          }}
        >
          {imageFilePaths.map((imageFilePath) => (
            <SplideSlide key={imageFilePath} className='d-block position-relative w-100 ratio ratio-1x1' style={{ maxWidth: `${setting.imageSize}px` }}>
                <Image width={setting.imageSize} height={setting.imageSize} className="d-block position-absolute top-0 start-0 bottom-0 end-0" src={`/images/${imageFilePath}`} alt={`fractal (${imageFilePath})`} />
                <div className='position-absolute d-flex justify-content-start align-items-center ps-2' style={{ height: '2rem', fontFamily: 'Consolas' }}>{imageFilePath}</div>
              </SplideSlide>
          ))}
        </Splide>
      </div>
    </>
  )
}

export async function getStaticProps (): Promise<{ props: Props }> {
  const imageFilePaths = fs.readdirSync('./public/images/').filter((imagePath) => !imagePath.startsWith('.')).sort(() => Math.random() - 0.5)
  return {
    props: {
      imageFilePaths
    }
  }
}
