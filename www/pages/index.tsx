import React from 'react'
import setting from '../setting'

export default function Home (): React.JSX.Element {
  return (
    <>
      <div id='Index' className='d-flex flex-column align-items-center'>
        <h1>{setting.title}</h1>
        {/* eslint-disable-next-line @next/next/no-img-element */}
        <img id='Logo' className='mt-3' style={{ width: '100%', maxWidth: '100px' }} src={`${setting.basePath}/tako.png`} alt='Logo' />
      </div>
    </>
  )
}
